package OI;


/**
 * ST表, 处理静态区间最值问题.
 */
public class ST {
    private int[][] table;
    private int type;

    /**
     * 构造函数.
     * 时间: O(nlogn).
     * 空间: O(nlogn).
     * @param nums 用于生成ST表的数组.
     * @param n 数组中有效数据的个数(考虑nums的前n个数).
     * @param type 取值为"max"或"min", 分别表示生成最大值或最小值的ST表.
     */
    public ST(int[] nums, int n, String type) {
        if(type.equals("max")) {
            this.type = 0;
        } else {
            this.type = 1;
        }
        math.initLog2(n+5);
        int k = math.log2[n] + 1;
        table = new int[k][n+5];
        for(int i = 1; i <= n; i++) {
            table[0][i] = nums[i];
        }
        if(this.type == 0) {
            for(int i = 1; i < k; i++) {
                for(int j = 1; j + (1 << i) - 1 <= n; j++) {
                    table[i][j] = math.max(table[i-1][j], table[i-1][j + (1 << i - 1)]);
                }
            }
        } else {
            for(int i = 1; i < k; i++) {
                for(int j = 1; j + (1 << i) - 1 <= n; j++) {
                    table[i][j] = math.min(table[i-1][j], table[i-1][j + (1 << i - 1)]);
                }
            }
        }
    }

    /**
     * 查询区间最值.
     * 时间: O(1).
     * 空间: O(1).
     * @param l 所查询区间左端点.
     * @param r 所查询区间右端点.
     * @return [l,r]的区间最值(按照所构造的ST表类型决定是最大值或最小值).
     */
    public int query(int l, int r) {
        int k = math.log2[r - l + 1];
        int res;
        if(this.type == 0) {
            res = math.max(table[k][l], table[k][r - (1 << k) + 1]);
        } else {
            res = math.min(table[k][l], table[k][r - (1 << k) + 1]);
        }
        return res;
    }

}
