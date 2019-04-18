class HeapStackDemo1 {
    public  static void main(String[] args) {
        // testStack(1);
        testHeap();
    }
    public static void testStack(int i) {
        if (i >= 6234) {
            return ;
        }
        System.out.println(i + " : hello world");
        int j = i + 1;
        testStack(j);
    }
    public static void testHeap() {
        // byte[] arr = new byte[1024 * 1024 * 512];
        // byte[] arr = new byte[1024 * 1024];
        int size = 1024 * 1024 * 1024;
        byte[][] arr = new byte[4][];
        arr[0] = new byte[size];
        arr[1] = new byte[size];
        System.out.println(arr);
    }
}
