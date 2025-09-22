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