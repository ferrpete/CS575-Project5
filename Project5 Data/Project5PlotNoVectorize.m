load('NoVectorizeData.txt')

threads = unique(NoVectorizeData(:,1));
arraySize = unique(NoVectorizeData(:,2));
peakPerformance = NoVectorizeData(:,3);
averagePerformance = NoVectorizeData(:,4);

peakPerformance = reshape(peakPerformance,length(arraySize),[]);

threadLegend = [];

for i=1:length(threads)
    
    threadLegend = [threadLegend, strcat(string(threads(i)), " Thread")];
    
end

nodeLegend = [];
color = linspecer(length(arraySize));

for i=1:length(arraySize)
    
    nodeLegend = [nodeLegend, strcat(string(arraySize(i)/1000000), " Million Entries")];
    
end

figure
plot(arraySize,peakPerformance, 'LineWidth',1.2)
xlabel('Array Size')
ylabel('Peak Performance, MegaRoots/Sec')
legend(threadLegend,'Location','NorthEastOutside')
axis([-inf,inf,-inf,inf])

figure
axes('NextPlot','replacechildren', 'ColorOrder',color); 
plot(threads,peakPerformance', 'LineWidth',1.2)
xlabel('Number of Threads')
ylabel('Peak Performance, MegaRoots/Sec')
legend(nodeLegend,'Location','NorthEastOutside')
axis([-inf,inf,-inf,inf])