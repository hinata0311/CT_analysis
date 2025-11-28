# Project: CE65 analysis in lab test at Kyorin Univ 2025-July 

**Analysts** : Kai Teramoto
**Institute** : Hiroshima University

## General Info

### Useful materials
* **CERN BOX** : https://cernbox.cern.ch/files/link/public/3YqeUsMt8VBPp40

### Data directory
```
$~/home/quark_hu/ct_202507/data
```
### Assigned data sets

| run number | kV | mA | phantom |
| --- | --- | --- | --- |
|66|120|400|TRUE|
|67|80|400|TRUE|
|68|80|400|FALSE|
|69|120|400|FALSE|

## How to use
### json config template

``` json
{
    "input_dir": "/home/teramoto/maps/ce65/kyorin/2507/data/tree/",
    "output_dir": "/home/teramoto/maps/ce65/kyorin/2507/data/hist/",
    "input_data_name": "ce65_ct2507_80kv_400ma_wF",
    "eve_max": -1,
    "clustering_method": "WINDOW",
    "skip_edge_seed": 2,
    "skip_edge_cluster": 1,
    "threshold_seed": 1000,
    "threshold_neighbor": 300
}
```

### configuration parameter keys

* `input_dir` : directory for input data
* `output_dir` : directory for output data
* `input_data_name` : data name. Don't include extension. i.g. not "data.root", just "data"
* `eve_max` : default is `-1`
* `clustering_method` : "CLUSTER" or "SEED" or "WINDOW". default is "SEED"
* `skip_edge_seed` : edge cut for seed pixel. default is "2"
* `skip_edge_cluster` :edge cut for global pixels. default is "1"
* `threshold_seed` : seed threshold. Should be Mandatorily defined
* `threshold_neighbor` : neighbor threshold. if you use "CLUSTER" method, automatically set to 0


## Execution
```bash
cd /project/dir/
make 
./build/run_basic_analysis <"path/to/your/configuration">
```

## Test
``` bash
cd /project/dir/
./test/src_test.sh
```

# srcの中身

## CE65TreeAnalyzer.cpp
* このファイルの中身は, includeファイルで宣言したHistogramを描写(実行した時に出てくる.rootファイルの中にあるもの)するコードと, そのHistogrmを作るためのlogicが記載されている。
calibrationを行うためには, ClusterCharge Distributionのみ見れば良い。他のヒストグラム(Hit mapやCluster Hit mapは確認するために使えばいいかな？)
MaskやCluster multiplicityなどはnoisyなpixelやローリングシャッターで不必要なデータを除外するために存在する。

## Cluster.cpp
* このファイルは, Clusterの基本情報(cluster sizeやclusterのchargeやそのseed pixelなど)をgetするための関数が記載されている。基本的にはこのコードは書き換えなくてもよい。
* もし, これよりも効率の良いClusterの情報の入手の仕方があれば, 書き換えてみて欲しい。

## RunControl.cpp
* この解析コードを動かすためのファイル。必要なヒストグラムを追加したいと思ってもこのファイルは書き変えるべきではない。


# Clustering method ; "Cluster" について
* これについては, 詳しくはhnakamuraのHEHI-J Workshop @ 熊本の発表資料を見れば分かる(mattermostを遡れば見れる。)
ざっくり説明すると, あるEvent frame でhit(deposited chargeとbase chargeの差分がseed thresholdを超えた時に出る判定)をdeposited chargeの高い順にsortする。
これを高い順に, そのhitしたpixelの四方八方の周りのpixelがhitしたかを判定する。
もし, hitしていたら, このpixelをClusterに加える。
この一連の操作を, "Cluster"と呼んでいる。
* (追記)
* Clustering method ; "Window"は, seed threshloldを超えているpixelをevent frameで探す。
* そのseed pixel (seed thresoldを超えたchargeを持つpixel)の周りの隣人がneighor thresholdを超えていたらneighor pixelとしてclusteに加える。
この一連の操作を, "Window"と呼んでいる。
* この""window" は選択すると, breakするように書かれているので選択しない方がいいかも。
* もしこの操作をしたい場合, 自身でソースコードを書き換える必要がある。

# config
* このファイル(.json)は, この解析コードを実行する時に必要なoptionを自由に変更するためのファイルである。
* 以下に必要なパラメータの説明を行う。
1. "input_dir"
これは, この解析コードに読み込ませるデータが所属しているディレクトリのpassを記載している。
2. "output_dir"
これは, この解析コードが吐き出す結果の.rootファイルのディレクトリのpassを記載している。
3. "eve_max"
このパラメータは, 読み込ませるデータをどのイベントまで解析させるかを指定するためのものである。もし, -1を選択したら, 全てのイベントを解析することができる。
4. "clustering_method"
ClusterとWindowを選択できる。それぞれの説明は上記に記したのでそれを参考にすると良い。
5. "skip_edge_seed"
忘れた。ソースコードを読んだらどんなパラメータか分かると思う。
6. "skip_edge_cluster"
チップの端は, バグが起こりやすいのであらかじめ消しておくことが重要である。これを行うためのパラメータがこれである。もし, 1を選択すると外側から1 pixelはclusteringに入れない　といったことが可能となる。
7. "threshold_seed"
seed thresholdの値を変更できるoption
8. "threshold_neigobor"
neighbor thresholdの値を変更できるoption
9. "calib_factor"
calibrationをするために必要な要素。これを今回は求めるのが君の課題だ。