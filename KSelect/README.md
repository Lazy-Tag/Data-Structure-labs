# Data_Structure_lab2

## RSelect核心算法实现

### 算法流程

首先找到找到相邻5个数的中间值组成一个数组mid，之后递归调用RSelect找到mid的中位数，即全局转数组的pivot点，之后利用找到的pivot点进行一次partition，找到pivot点对应在数组中的位置，之后根据pivot点的具体位置pos与K的关系，递归调用RSelect(l, pos- 1)或RSelect(pos + 1, r)。

### 时间复杂度递推式

$$
T(n) = T(\frac{n}{5}) + T(\frac{7n}{10}) + O(n)
$$

总时间复杂度为$O(n)$。

### 代码实现

```C++
int RSelect(vector<int>& w, int l, int r, int k) {
    if (r - l + 1 <= LEN) {
        sort(w.begin() + l, w.begin() + r + 1);
        return k;
    }
    vector<int> mid;
    mid.push_back(0);
    for (auto i = l; i < r; i += 5 ) mid.push_back(midSelect(w, i));
    int size = mid.size();
    int it = FSelect(mid, 1, size - 1, size >> 1), p = 0;
    for (int i = l; i <= r; i ++ )
        if (w[i] == mid[it])
            p = i;
    int len = Partition(w, l, r, p);
    if (len == k) return k;
    else if (len < k) return FSelect(w, len + 1, r, k);
    return FSelect(w, l, len - 1, k);
}
```

## 运行时间比较

我们比较了数据量在$1e6 - 1e9$的三种求第K大数的算法为KSelect, MergeSort. RSelect运行时间如下

![image-20230307201618844](https://s2.loli.net/2023/03/07/jnh2oPbSMlG4wI6.png)

## YOJ通过截图



![运行截图](https://s2.loli.net/2023/03/07/mFC2UJjBtfyMAgD.png)
