class ConstructorDemo1 {
    public static void main(String[] args) {
        System.out.println("begin---");
        Dog d = new Dog();
        d.watch();
        Dog d1 = new Dog();
        d1.watch();
    }
}

class Dog {
    // 构造代码块

    static {
        //System.out.println("1===>开始创建Dog()!!" + name);
        name = "旺财";
        System.out.println("hehe");
        //System.out.println("1===>开始创建Dog()!!" + name);
    }
    // 构造代码块
    {
        //System.out.println("2===>开始创建Dog()!!" + name);
        name = "小强";
        //System.out.println("1===>开始创建Dog()!!" + name);
    }

    private static String name = "无名";
    private String color;

    public Dog() {
        System.out.println("new Dog()" + name);
    }
    // 
    public void watch() {
        System.out.println("汪汪~~~~~");
    }
}
