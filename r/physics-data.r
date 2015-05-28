options(digits = 7)

data <- c(
    1.020, 1.260, 1.320, 1.410, 1.440, 0.920, 1.290, 1.190, 1.210, 1.560,
    1.200, 1.400, 1.190, 1.210, 1.960, 1.350, 1.060, 1.380, 1.180, 1.310,
    1.350, 0.880, 1.220, 1.220, 1.440, 1.050, 1.070, 1.280, 1.360, 1.090,
    0.940, 0.960, 1.360, 1.430, 1.200, 1.530, 1.160, 1.240, 1.520, 1.250,
    1.110, 1.450, 1.110, 0.910, 1.140, 1.060, 1.220, 1.360, 1.310, 1.230
)
print(hist(data, xlim=c(0.8, 1.6), breaks = 10))
n <- length(data)

average = mean(data)
print(average)

tmpsum = 0

data_averages = data - average
data_averages_squares = data_averages^2

table <- data.frame(measure = data, avg = data_averages, avg2 = data_averages_squares)

cat("\n")
print(table)

avg2sum <- sum(data_averages_squares)
delta1 <- sqrt(avg2sum/(n-1))
delta2 <- sqrt(avg2sum/(n*(n-1)))
cat("avg =", average)
cat("\navg2sum =", avg2sum)
cat("\ndelta1 =", delta1)
cat("\ndelta2 =", delta2)
