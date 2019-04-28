/**
 * extends继承
 * super()调用父类的构造函数
 **/
class ExtendDemo2 {
    public static void main(String[] args) {
        BMWSportCar bmw = new BMWSportCar();
    }
}

class Car {
    public String color;
    public void run() {
        System.out.println("move~~~~");
    }
    public  Car() {
        this.color = color;
        System.out.println("new Car()");
    }
}

class SportCar extends Car {
    public int velocity;
    public SportCar(int velocity) {
        this.velocity = velocity;
        System.out.println("new SportCar()");
    }
}

class BMWSportCar extends SportCar {
    public int price;
    public BMWSportCar() {
        super(200);
        System.out.println("new BMWSportCar()");
    }
}
