#Zachary Job
#10/20/15

#Generic init
rm(list=ls())

library(kknn)
library(class)

#Defs
norm <- function(x)
{
	return((x - min(x)) / (max(x) - min(x)))
}

writeLines("\nPerforming...\n")

getCSV = read.csv("../DATA_IMG/output.csv", header = TRUE)

#Initialization
loopNum = 1
sampleSz = 12
labelLoc = 13
l0 = 13
diff0 = 0
#normalize iris into dataSet
dataSet <- as.data.frame(getCSV)
dataSet[dataSet == 0] <- 0.00001
szRow <- nrow(dataSet)
szCol <- ncol(dataSet)

#generate samples
samples <- sample(szRow,as.integer((1 - (1 / (sampleSz))) * szRow))

#get the data and set some final variables
testData <- dataSet[-samples,]
testSz = nrow(testData)
testNames = testData[,szCol]
trainData = dataSet[samples,]

#show the data
writeLines("::TEST::")
print(testData)
writeLines("\n::TRAINING::")
print(trainData)

#Perform the algorithm and display for 1
Labeling <- testData$TYPE
a <- testData$Q1W
b <- testData$Q2W
c <- testData$Q3W
d <- testData$Q4W
e <- testData$Q1STD
f <- testData$Q2STD
g <- testData$Q3STD
h <- testData$Q4STD
i <- testData$QSTD
j <- testData$Q1_2STD
k <- testData$Q2_3STD
l <- testData$Q3_4STD
writeLines("")
result0 <- kknn(Labeling~a+b+c+d+e+f+g+h+i+j+k+l,trainData[,-labelLoc],testData[,-labelLoc],trainData[,labelLoc],l0)

#Count up the differences
for(i in 1:testSz)
{
	if(identical(testNames[i], result0$fit[i]) == FALSE)
	{
		diff0 = diff0 + 1
	}
}

writeLines("\nResults...")
sprintf("K %d -> %f", l0, (100/testSz) * (testSz - (diff0 / loopNum)))

writeLines("\nCleaning...")

#Generic closure
rm(list=ls())
