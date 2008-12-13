%dataSet=importVPS(fileLocation)
function dataSet=importVPS(fileLocation)

	ConfigBits = 24;
	LineLength = 33;

	% open file
	fid = fopen(fileLocation);

	% find out how long the file is
	fseek(fid, 0, 'eof');
	fileLen = ftell(fid) + 1 - ConfigBits;

	% go to the beginning of the file
	fseek(fid, 0, 'bof');

	% optimize memory
	pack;
	
	% initialize variables
	polarity = [0,1,0,-1,0,1,0];
	totalLines = floor(fileLen/LineLength);

	% read config vales
	dataSet.ACLK = hex2dec(fgets(fid, 8));
	dataSet.DEC = hex2dec(fgets(fid, 8));
	dataSet.MODE = hex2dec(fgets(fid, 8));

	fprintf('Importing data, total lines to import: %d\n', totalLines);

	% pre-allocate data
	spacers(8) = 0;
	tempData(7) = 0;
	dataSet.data(totalLines,9) = 0;
	dataSet.counter(totalLines,1) = 0;
	secondary(totalLines) = 0;
	currentPercent = 0;
	nextPercent = totalLines/100;
	
	fprintf(1, '  0%% Complete.\n');

	while (fileLen >= LineLength)

		bitsMisaligned = false;

		%read next line
		% read count
		tempCount = fread(fid, 1, 'uint32=>uint32');

		% read spacers
		spacers = fread(fid, 8, 'uint8', 3);
		% read data
		fseek(fid, -31, 'cof');
		tempData = fread(fid, 7,'bit24=>int32', 8);

		fileLen = fileLen - LineLength;

		%make sure there aren't any missing bits
		for j=1:7
			if (spacers(j) ~= 9)
				bitsMisaligned = true;
			end;
		end;

		if (spacers(8) ~= 10)
			bitsMisaligned = true;
		end;
		
		if (bitsMisaligned == true)
			fprintf(1, 'Misaligned bits found on line %d\n', tempCount);

			% scan forward until we find an end of line character AND
			%  there is another LineLength bytes later.
			while ((bitsMisaligned == true) && (fileLen > LineLength))
				temp = 0;
				while ((temp ~= 10) && (fileLen > LineLength))
					temp = fread(fid, 1, 'uint8');
					fileLen = fileLen - 1;
				end

				if (fileLen <= LineLength)
					break;
				end;
				
				fseek(fid, 39, 'cof');
				
				temp = fread(fid, 1, 'uint8');

				fseek(fid, -LineLength, 'cof');
	
				if (temp == 10)
					bitsMisaligned = false;
				end;
			end;
		
		else
			%save line
			dataSet.counter(tempCount+1,1) = tempCount;
			dataSet.data(tempCount+1,1:6) = (tempData(1:6)).';
			secondary(tempCount+1) = tempData(7);
		
			if (tempCount == floor(nextPercent))
				currentPercent = currentPercent + 1;
				fprintf(1, '%3.0f%% Complete.\n', currentPercent);
				nextPercent = nextPercent + totalLines/100;
			end;
		end;
	end;

	fclose(fid);

	fprintf(1, 'Data inport done, now filling out secondary cells . . .\n');
	
	j = 0;
	prev = dataSet.data(1,:);
	for i = 1:(length(secondary)-2)
		% fill out secondary sensors
		dataSet.data(i:i+2,7+j) = secondary(i);	
		j = mod(j+1,3);

		%make magnetometer polarity/bias calculation
		current = dataSet.data(i,:);
		
		for k=2:2:6
			dataSet.data(i,k) = polarity(k)*((dataSet.data(i,k)-prev(1,k))/2);
		end

		prev = current;
		
		polarity = polarity*-1;
	end;

	%disregard first and last two lines
	dataSet.data = dataSet.data(3:length(dataSet.data(:,1))-2,:);
	dataSet.counter = dataSet.counter(3:length(dataSet.counter(:,1))-2,:);

    dataSet.raw.accel.X = dataSet.data(:,1);
    dataSet.raw.mag.X = dataSet.data(:,2);
    dataSet.raw.accel.Y = dataSet.data(:,3);
    dataSet.raw.mag.Y = dataSet.data(:,4);
    dataSet.raw.gyro = dataSet.data(:,5);
    dataSet.raw.mag.Z = dataSet.data(:,6);

    
    
    