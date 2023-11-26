rm *.csv
nvcc -o cublas cublas.cu -lcublas

for ((i=1; i<=512; i*=2)); do
  ./cublas $i
done
rm cublas


for ((i=1; i<=512; i*=2)); do
  python3 pymult.py $i
done

python3 graph.py