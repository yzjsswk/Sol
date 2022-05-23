package OI;

public class math {
    public static int max(int a, int b) {
        return a > b ? a : b;
    }
    public static int min(int a, int b) {
        return a < b ? a : b;
    }
    public static int[] log2;
    public static void initLog2(int n) {
        log2 = new int[n+5];
        log2[0] = -1;
        for(int i = 1; i <= n; i++) {
            log2[i] = log2[i>>1] + 1;
        }
    }

}