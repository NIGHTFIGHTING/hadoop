class ConstructorDemo2 {
    public static void main(String[] args) {
        Dog d = new Dog("大黄", "yellow");
        System.out.println(d.name + "," + d.color);
    }
}

class Dog {
    public String name;
    public String color;
    
    public Dog(String name) {
        this.name = name;
    }
    public Dog(String name, String color) {
        this(name);
        // this.name = name;
        this.color = color;
    }
}
