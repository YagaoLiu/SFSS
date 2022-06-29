library(Rcpp)
sourceCpp("lis.cpp")

LISmatrix =  function(strs,n,k) {
  KmerTable = list()
  kmers = list()
  maxLIS = length(strs) - k + 1
  for(i in 1:n){
    order = vector()
    kmertable = list(vector())
    x = strs[i]
    for(j in k:nchar(x)){
      order = c(order, substr(x,j-k+1,j))
      sub = substr(x,j-k+1,j)
      kmertable[[sub]] = c(kmertable[[sub]],j-k+1)
    }
    kmers[[i]] = order
    KmerTable[[i]] = kmertable
  }
  LIS_matrix = matrix(nrow = n, ncol = n)
  for(i in 1:n){
    for(j in 1:n){
      if(i == j){
        LIS_matrix[i,j] = maxLIS[i]
      }
      IndexSeq = unlist(KmerTable[[j]][kmers[[i]]])
      if(length(IndexSeq) == 0){
        LIS_matrix[j,i] = 0
      }else{
        LIS_matrix[j,i] = LongestIncreasingSubsequenceLength(IndexSeq)
      }
    }
  }
  # DM_matirx = LIS_matrix + t(LIS_matrix)
  # for(i in 1:n){
  #   for(j in i:n){
  #     DM_matrix[j,i] = 1 - (DM_matirx[j,i]) / (maxLIS[i]+maxLIS[j])
  #   }
  # }
  # dm = as.dist(DM_matirx)
  return(LIS_matrix)
}

LISdm = function(LISmx, l, k){
  n = length(l)
  dm = LISmx
  for(i in 1:n){
    for(j in i:n){
      dm[j,i] = l[i]+l[j]-2*k+2- (LISmx[i,j]+LISmx[j,i])
    }
  }
  return(as.dist(dm))
}
