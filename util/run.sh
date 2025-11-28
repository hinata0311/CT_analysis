cd /home/hinata/kyorin/analysis/ce65-ct-2507
make clean
make 
echo "make completed"
echo "Start analysis w/ phantom"
#./build/run_basic_analysis config/80kv_400ma_wF.json
echo "Start analysis w/o phantom"
./build/run_basic_analysis config/80kv_400ma_wF.json
echo "Finished the process" 