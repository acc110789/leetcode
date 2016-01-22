漢字拼音首字母
---------------

在網上以“汉字拼音首字母”作爲關鍵字搜索，大部分的解法是iconv轉換成GB2312編碼，
然後查ASCII碼對照表，該方法無法處理繁體字！

而使用libgooglepinyin 的原始字典 rawdict_utf8_65105_freq.txt 可以查到收錄的
繁體字對應的讀音。


## Profile

```
./pinyin 
gprof ./pinyin gmon.out > profile
```
