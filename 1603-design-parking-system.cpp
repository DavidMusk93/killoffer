/**
 * Constrains: 0<=b,m,s<=1000
 * java: thread pool,atomic
 */
class ParkingSystem {
public:
    ParkingSystem(int big, int medium, int small) {
        i_ = big;
        i_ |= medium << 10;
        i_ |= small << 20;
    }

    bool addCar(int carType) {
        static int MASK = 0x3ff;
        carType = (carType - 1) * 10;
        if (i_ & (MASK << carType)) {
            i_ -= 1 << carType;
            return true;
        }
        return false;
    }

private:
    int i_;
};

/**
 * Your ParkingSystem object will be instantiated and called as such:
 * ParkingSystem* obj = new ParkingSystem(big, medium, small);
 * bool param_1 = obj->addCar(carType);
 */
