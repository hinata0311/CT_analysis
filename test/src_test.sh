cd ~/maps/ce65/kyorin/2507/analysis/
make clean
make
mv build/ce65dict_rdict.pcm build/lib/

echo "Completed building, just start test run !"
echo "------------------------------------------------------------------------------------------------"
./build/run_basic_analysis test/test.json