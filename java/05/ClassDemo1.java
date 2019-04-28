class ClassDemo1 {
    public  static void main(String[] args) {
        Person p = new Person();    // 创建对象
        System.out.println(p);
        p.run();
        System.out.println(p.name);
        System.out.println(p.age);
        System.out.println(p.run());
    }
}

class Person{
    // 类成员变量
    String name = "好人";
    int age = 10;
    // 成员函数
    int run() {
        System.out.println("run...");
        return 10;
    }
}
