/**
 * extends继承,考察构造代码块 + 构造函数
 **/
class ExtendDemo3 {
    public static void main(String[] args) {
        BMWSportCar mycar = new BMWSportCar();
        mycar.velocity = 200;
        mycar.price = 300;
        mycar.run();
        mycar.setColor("red");
        mycar.setColorPro("green");
        System.out.println(mycar.getColor());
    }
}

class Car {
    // 私有属性
    private String color;
    {
        System.out.println("Cons Block in Car");
    }
    public  Car() {
        this.color = color;
        System.out.println("new Car()");
    }
    public String getColor() {
        return color;
    }
    public void setColor(String color) {
        System.out.println("setColor: " + color );
        this.color = color;
    }
    public void run() {
        System.out.println("move~~~~");
    }
}

class SportCar extends Car {
    public int velocity;
    {
        System.out.println("Cons Block in sportCar");
    }
    public SportCar(int velocity) {
        this.velocity = velocity;
        System.out.println("new SportCar()");
    }
    /*public void setColor(String color) {
        System.out.println("sportCar.setColot(), is it a good color??");
        super.setColor(color);
    }*/
    public void setColorPro(String color) {
        System.out.println("is it a good color??");
        this.setColor(color);
        //super.setColor(color);
    }
}

class BMWSportCar extends SportCar {
    public int price;
    {
        System.out.println("Cons Block in BM@SportCar");
    }
    public BMWSportCar() {
        super(200);
        System.out.println("new BMWSportCar()");
    }
}
