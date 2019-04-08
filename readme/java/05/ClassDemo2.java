class ClassDemo2 {
    public  static void main(String[] args) {
        Dog d1 = new Dog();
        d1.name = "旺财";
        d1.color = "white";
        d1.watch();
        System.out.println(d1.name);
        
        Dog d2 = new Dog();
        d2.watch();
        System.out.println(d2.name);
        buyDog(d1);
        buyDog(d2);
        
        System.out.println("");
        System.out.println("匿名对象1.------------");
        // 匿名对象
        new Dog().catchMouse();
        System.out.println("匿名对象2.------------");
        Dog d3 = buyDog(new Dog());
        System.out.println(d3.name);
        d3 = buyDog(d1);
        System.out.println(d3.name);
    }
    public static Dog buyDog(Dog d) {
        System.out.println("开始买狗");
        System.out.println("毛色 : " + d.color + ", 名字 : " + d.name);
        System.out.println("买卖结束了!");
        return d;
    }
}

class Dog {
    String name ;
    String color ;
    void watch() {
        System.out.println("有人来了,汪汪汪...");
    }
    void catchMouse() {
        System.out.println("抓了只老鼠,");
    }
}
