import OI.*;


public class JavaSol {

    static int n = 100000;
    static int[] a = new int[n+5];


    public static void main(String[] args) {
        for(int i = 0; i < n; i++) {
            a[i] = i;
        }
        ST st = new ST(a, n, "max");
        System.out.println(st.query(5465, 54455));
        System.out.println(math.log2[10016]);
    }    
}
