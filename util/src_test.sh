cd ~/kyorin/analysis/
make clean
make
mv build/ce65dict_rdict.pcm build/lib/
./build/run_basic_analysis ct_68_250731_ctOn_woF_long 1000 100
./build/run_basic_analysis ct_68_250731_ctOn_woF_long 1000 300
./build/run_basic_analysis ct_68_250731_ctOn_woF_long 1000 500
./build/run_basic_analysis ct_68_250731_ctOn_woF_long 500 100
./build/run_basic_analysis ct_68_250731_ctOn_woF_long 500 300
./build/run_basic_analysis ct_68_250731_ctOn_woF_long 500 500
