class ConstructorDemo1 {
    public static void main(String[] args) {
        Dog d = new Dog();
    }
}

class Dog {
    private String name;
    private String color;
    // 
    public void watch() {
        System.out.println("汪汪~~~~~");
    }
}
