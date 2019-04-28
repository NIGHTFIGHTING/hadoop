class ExtendDemo1 {
    public static void main(String[] args) {
        Jing8 jing8 = new Jing8();
        jing8.name = "dahuang";
        jing8.watch();
        jing8.owner = "laozhang";
    }
}

class Animal {
    public String name;
    public int weight;
    public void move() {
        System.out.println("move~~~~");
    }
}

class Dog extends Animal {
    public void watch() {
        System.out.println("ren ren");
    }
}

class Jing8 extends Dog {
    public String owner;
}
