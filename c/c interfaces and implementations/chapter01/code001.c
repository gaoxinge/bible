int dotProduct(int x[], int y[], int n) {
    int i, sum;
    
    sum = 0;
    for (i = 0; i < n; i++)
        sum += x[i]*y[i];
    return sum;
}