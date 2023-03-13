public class ComplexNum {

    private double deystv;
    private double mnim;

    public ComplexNum(double num1, double num2) {
        this.deystv = num1;
        this.mnim = num2;
    }

    public ComplexNum(double num) {
        this(num, 0);
    }

    public ComplexNum() {
        this(0);
    }

    public double getDeystv() {
        return deystv;
    }

    public double getMnim() {
        return mnim;
    }

    public void setDeystv(double deystv) {
        this.deystv = deystv;
    }

    public void setMnim(double mnim) {
        this.mnim = mnim;
    }

    public ComplexNum sum(ComplexNum complNum1) {
        double deystv1 = this.deystv + complNum1.getDeystv();
        double mnim1 = this.mnim + complNum1.getMnim();
        return new ComplexNum(deystv1, mnim1);
    }

    public ComplexNum sub(ComplexNum complNum1) {
        double deystv1 = this.deystv - complNum1.getDeystv();
        double mnim1 = this.mnim - complNum1.getMnim();
        return new ComplexNum(deystv1, mnim1);
    }

    public ComplexNum mult(ComplexNum complNum1) {
        double deystv1 = this.deystv * complNum1.getDeystv();
        double mnim1 = this.mnim * complNum1.getMnim();
        return new ComplexNum(deystv1, mnim1);
    }

    public double modul() {
        double deystv1 = Math.pow(this.deystv, 2);
        double mnim1 = Math.pow(this.mnim, 2);
        double sum = deystv1 + mnim1;
        return Math.sqrt(sum);
    }
}