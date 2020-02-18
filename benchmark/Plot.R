### Graphs of benchmark

setwd("/home/angela/Documenti/Advanced Programming/AP_BST/benchmark")

folder <- "Sissa-nSampl=50"
path_plots <- paste0("./Data/",folder,"/")
path_outputs <- paste0("./Data/",folder,"/")

## save the workspace
save.image(paste0(path_plots, folder, ".RData"))

## load the workspace
load(paste0(path_plots, folder, ".RData"))

library(Hmisc)

s <- c("benchmark_times_tree.txt", "benchmark_times_btree.txt", "benchmark_times_map.txt")
leng <- length(s)

nbin = 1

for (k in 1:leng) {
  p <- as.matrix(read.table(paste0(path_outputs, s[k]), header = TRUE))
  nStart <- p[1]
  nIncr <- p[2]
  nEnd <- p[3]
  nSampl <- p[4]
  if (k == 1) {
    meanData <- matrix(0, nrow = leng, ncol = nEnd/nIncr)
    sdData <- matrix(0, nrow = leng, ncol = nEnd/nIncr)
  }
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
    meanData[k, m/nStart] <- mean(v)
#    sdData[k, m/nStart] <- sd(v)
    
    # binning technique
    lbin <- size/nbin
    temp <- seq(0,0, l = nbin)
    temp2 <- seq(0,0, l = nbin)
    for(b in 1:nbin) {
      temp[b] <- mean(v[(1+(b-1)*lbin):(b*lbin)])
      temp2[b] <- sd(v[(1+(b-1)*lbin):(b*lbin)])
    }
    sdData[k, m/nStart] <- mean(temp2)/sqrt(nbin)
#    sdData[k, m/nStart] <- sd(temp)/sqrt(nbin)
    
    incr <- incr + size
  }
}

meanData <- meanData/nSampl
sdData <- sdData/nSampl

maxylim <- max(as.numeric(meanData)) + 20
png(width=14, height=8, units = "cm", res = 300, pointsize = 8, file=paste0(path_plots, "benchmark.png"))
par(mar=c(3,3,2,1), mgp=c(2, 0.5, 0)) # mar=c(bottom, left, top, right), c(axis title, axis labels, axis line). default: mar=c(5, 4, 4, 2) + 0.1, mgp=c(3, 1, 0)
errbar(nrange, meanData[1, ], meanData[1,]+sdData[1,]/2, meanData[1,]-sdData[1,]/2, type="p", pch = 21, col = 3, bg = 3, ylim = c(0, maxylim), xlab = "Number of Nodes in the tree", ylab = "Time [ns]", cex.axis=1, cex.lab=1)
lines(nrange, meanData[1, ], col = 3)
errbar(nrange, meanData[2, ], meanData[2,]+sdData[2,]/2, meanData[2,]-sdData[2,]/2, add = TRUE, pch = 21, col = 4, bg = 4)
lines(nrange, meanData[2, ], col = 4)
errbar(nrange, meanData[3, ], meanData[3,]+sdData[3,]/2, meanData[3,]-sdData[3,]/2, add = TRUE, pch = 21, col = 2, bg = 2)
lines(nrange, meanData[3, ], col = 2)
title("Benchmark on `find()`", adj = 0.5, line = 0.5, cex.main = 1.2)
legend(x = nStart, y = 60, legend=c("APbst::bst", "Balanced APbst::bst", "std::map"), col = c(3, 4, 2), lty=1, cex=0.85)
dev.off()

# png(width=1366, height=810, pointsize=25, file=paste0(path_plots,"benchmark2.png"))
# par(mar=c(3.5,3.5,2.5,1), mgp=c(2, 0.5, 0))  # mar=c(bottom, left, top, right), c(axis title, axis labels, axis line). default: mar=c(5, 4, 4, 2) + 0.1, mgp=c(3, 1, 0)
# errbar(nrange, meanData[1, ], meanData[1,]+sdData[1,]/2, meanData[1,]-sdData[1,]/2, type="p", pch = 21, col = 3, bg = 3, ylim = c(0, maxylim), xlab = "Number of Nodes in the tree", ylab = "Time [ns]", cex.axis=1, cex.lab=1)
# lines(nrange, meanData[1, ], col = 3)
# errbar(nrange, meanData[2, ], meanData[2,]+sdData[2,]/2, meanData[2,]-sdData[2,]/2, add = TRUE, pch = 21, col = 4, bg = 4)
# lines(nrange, meanData[2, ], col = 4)
# errbar(nrange, meanData[3, ], meanData[3,]+sdData[3,]/2, meanData[3,]-sdData[3,]/2, add = TRUE, pch = 21, col = 2, bg = 2)
# lines(nrange, meanData[3, ], col = 2)
# title("Benchmark on `find()`", adj = 0.5, line = 0.5, cex.main = 1)
# legend(x = nEnd - 7*nStart, y = maxylim, legend=c("APbst", "Balanced APbst", "std::map"), col = c(3, 4, 2), lty=1, cex=0.7)
# dev.off()


# meanData <- data.frame(meanData)
# ggplot(meanData, aes(x = nrange, y = meanData[1, ])) + 
#   geom_line(color = 3) +
#   geom_errorbar(aes(x=nrange, ymin=meanData[1,]-sdData[1,]/2, ymax=meanData[1,]+sdData[1,]/2), width=0.4, colour=3, size=1.3)
