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
