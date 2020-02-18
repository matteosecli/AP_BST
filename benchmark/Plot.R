### Graphs of Exercise 0 - hybrid

setwd("/home/angela/Documenti/Advanced Programming/AP_BST/")

## save the workspace
save.image("./data1.RData")

## load the workspace
load(paste0(path_plots, "data.RData"))

library(Hmisc)


p <- as.matrix(read.table("benchmark_times.txt"))
nStart <- p[1]
nIncr <- p[2]
nEnd <- p[3]
nSampl <- p[4]
meanData <- seq(0, 0, l=nEnd/nIncr)
sdData <- seq(0, 0, l=nEnd/nIncr)
incr <- 4
nrange <- seq(from=nStart, to=nEnd, by=nIncr)
for (m in nrange) {
  incr <- incr + 1
#  print(incr)
  nCurrent <- p[incr]
#  print(nCurrent)
  size <- nCurrent/nSampl
#  print(size)
  v <- seq(0, 0, l = size)
  for(j in 1:size) {
    v[j] <- p[incr + j]
  }
#  print(v)
  meanData[m/nStart] <- mean(v)
  sdData[m/nStart] <- sd(v)
  
  incr <- incr + size
}

meanData <- meanData/nSampl
sdData <- sdData/nSampl

maxylim <- max(as.numeric(meanData))
png(width=8, height=6, units = "cm", res = 300, pointsize = 10, file=paste0(path_plots, "benchmark.png"))
par(mar=c(3,2.5,1,1), mgp=c(1.5, 0.5, 0)) # mar=c(bottom, left, top, right), c(axis title, axis labels, axis line). default: mar=c(5, 4, 4, 2) + 0.1, mgp=c(3, 1, 0)
#plot(nrange, meanData, type="p", pch = 21, col = 3, bg = 3, xaxt = "n", ylim = c(0, maxylim), xlab = "Number of Nodes in the tree", ylab = "Time [ns]", cex.axis=.75, cex.lab=.75)
errbar(nrange, meanData, meanData+sdData/2, meanData-sdData/2, type="p", pch = 21, col = 3, bg = 3, xaxt = "n", ylim = c(0, maxylim), xlab = "Number of Nodes in the tree", ylab = "Time [ns]", cex.axis=.75, cex.lab=.75)
lines(nrange, meanData, col = 3)
#points(nrange, tot[2, ], pch = 21, col = 4, bg = 4)
#lines(nrange, tot[2, ], col = 4)
#points(nrange, tot[3, ], pch = 21, col = 5, bg = 5)
#lines(nrange, tot[3, ], col = 5)
title("Benchmark on `find()`", adj = 0.5, line = 0.5, cex.main = .75)
axis(1, at = nrange, labels = nrange, cex.axis = .75)
legend(x = nStart, y = maxylim, legend="APbst", col = 3, lty=1, cex=0.7)
#legend(x = 1, y = maxylim, legend=c("std::map", "APbst", "Balanced APbst"), col = c(3, 4, 5), lty=1, cex=0.7)
dev.off()
