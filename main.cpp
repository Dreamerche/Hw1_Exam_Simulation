#include <iostream>

class Lektor{
    private:
        int timeLate;
        int timeGrading;//minuti za ocenqvane na edna rabota
        Student* currentlyGrading;
        int timeUsed;//izminalo vreme

    public:
        ~Lektor(){
            delete [] currentlyGrading;
        }
        Lektor():timeLate(0), timeGrading(5){}//good lektor
        Lektor(int L, int C): timeLate(L), timeGrading(C){}

        const int getTimeUsed() const{
            return timeUsed;
        }
        void addToTimeUsed(){
            timeUsed++;
        }
        const int getTimeGrading() const{
            return timeGrading;
        }

        const Student getStudent() const{
            return currentlyGrading;
        }
        void removeStudent(){
            delete currentlyGrading;
            currentlyGrading=nullptr;
            timeUsed=0;
        }
        void setStudent(const Student& newCurr){
            currentlyGrading=newCurr;
        }
};



class Student{
    private:
        int arrivalTime=0;//arrival time after the exam's start
        char* fN=nullptr;//fakulteten nomer
        int timeTest=30;//the time needed to finish the test
        int course=2;

    public:
        ~Student(){
            delete [] fN;
        }
        Student(){}
        Student(int t, const char* F, int T, int K):arrivalTime(t),timeTest(T),course(K){
            if(F!=nullptr){
                while (F!=nullptr)
                {
                    *fN=*F;
                    fN++;
                    F++;
                }
            }
        }
        void getStudentInfo(){
            std::cout<<fN<<", "<<course<<" kurs, zakusnqva s "<<arrivalTime<<" min i mu trqbvat "<<timeTest<<" min da reshi izpita.";
            std::cout<<std::endl;
        }



};

class Seat{
    private:
        int index;//za poveche udobstvo
        char type;//Occupied, Free ili Broken, ama shte dobavq i edin da ne se zaema - N
        bool occupied=false;
        Student* student=nullptr;//koi student v momenta e zael mqstoto
        int timeUsed=0;//kolko vreme dosega e sedql studentut

    public:
    Seat(){}
    Seat(int i, char t, bool oc):index(i), type(t), occupied(oc){}
    void getSeatInfo(){
        std::cout<<index<<": "<<type<<", "<<occupied<<"\nStudent: ";
        if(student==nullptr){
            std::cout<<"none";
            std::cout<<std::endl;
        }
        else{
            (*student).getStudentInfo();
        }

    }
    const char getType() const{
        return type;
    }


};
class Room{
    private:
        int N;
        int M;
        int countB=0;
        int* B=nullptr;
        Seat* seats=nullptr;//vsichki mesta za sqdane
    
    public:
        ~Room(){
            if (B != nullptr) {
                delete [] B;
        }
        }
        Room():N(5), M(5),countB(0){}//default-che za kusmet, oh, poludqvam
        Room(int rows, int cols, int countB, const int* broken): N(rows), M(cols),countB(countB){
             if (broken != nullptr && countB!=0) {
                B = new int[countB+1];
                for (int i = 0; i < countB; i++) {
                    B[i] = broken[i];
                }
            }
            generateSeats();
        }

        Room(const Room& other){
            if(this!=&other){
                this->N=other.N;
                this->M=other.M;
                this->countB=other.countB;
                if (other.B != nullptr) {
                    B = new int[countB+1];
                    for (int i = 0; i < countB; i++) {
                        B[i] = other.B[i];
                    }
                }
            }
            generateSeats();
        }

        Room& operator=(const Room& other) {
            if(this!=&other){
                Room copy(other);
                swap(copy);
                generateSeats();
            }
            return *this;
        }

        void generateSeats(){//mnogo vajna func
            delete [] seats;
            seats=new Seat[N*M];
            int helpCount=0;
            for (size_t i = 0; i < N; i++)
            {
                for (size_t j = 0; j < M; j++)
                {
                    int index=i*M+j;
                    if((B!=nullptr && helpCount<countB) && index==B[helpCount]){//tuka se nadqvam v B da sa posledovatelni indexi
                        Seat s=Seat(index,'B',false);
                        seats[index]=s;
                        helpCount++;
                    }
                    else if(i%2==1 || j%2==1){
                        Seat s=Seat(index,'N',false);
                        seats[index]=s;
                    }
                    else{
                        Seat s=Seat(index,'F',false);
                        seats[index]=s;
                    }
                }
            }         
        }

        void printSeats(){
            std::cout<<"print the seatssss\n";
            for (size_t i = 0; i < N; i++)
            {
                for (size_t j = 0; j < M; j++)
                {
                    std::cout<<seats[i*M+j].getType()<<" ";
                }
                std::cout<<std::endl;
            }

            for (size_t i = 0; i < N; i++)
            {
                for (size_t j = 0; j < M; j++)
                {
                    int index=i*M+j;
                    Seat s=seats[index];
                    s.getSeatInfo();
                }
                std::cout<<std::endl;
            }
        }

        void swap(Room& other) {
            std::swap(N, other.N);
            std::swap(M, other.M);
            std::swap(countB, other.countB);
            std::swap(B, other.B);
        }

void printBrokenIndexes(){
    if (B != nullptr) {
        for (int i = 0; i < countB; i++) {
            std::cout << B[i] << " ";
        }
        std::cout << std::endl;
    } 
   else{
        std::cout << "No broken seats!" << std::endl;
   }
}


        void printRoomSeats(){//room's type and condition
            //std::cout<<"hohoho";
            for (size_t i = 0; i < N; i++)
            {
                for (size_t j = 0; j < M; j++)
                {
                    int index=i*M+j;
                    char sType=seats[index].getType();
                    std::cout << sType << " ";
                }
                std::cout<<std::endl;
            }
        }

        void printRoomsSeatsDetails(){
             for (size_t i = 0; i < N; i++)
            {
                for (size_t j = 0; j < M; j++)
                {
                    int index=i*M+j;
                    Seat s=seats[index];
                    s.getSeatInfo();
                }
                std::cout<<std::endl;
            }
}

        
void printRoomSeatsNulevo(){//eto kak shte se zapulnqt
            //std::cout<<"hohoho";
            for (size_t i = 0; i < N; i++)
            {
                for (size_t j = 0; j < M; j++)
                {
                    int index=i*M+j;
                    char seat=seats[index].getType();
                    if(seat=='F'){
                        seat='O';
                    }
                    else if(seat=='N'){
                        seat='F';
                    }
                    
                    std::cout << seat << " ";
                }
                std::cout<<std::endl;
            }
            
        }
};




class Simulation{
    private:
        Room room;
        Lektor lektor;
        std::queue<Student> waiting;
        std::stack<Student> ungraded;//neoceneni raboti, ama ne mi se pravi klas izpit
        std::stack<Student> graded;//ne sum sigurna dali shte e stek, ama bi trqbvalo lektorut da raboti
        //sus stekove ot listi raboti
        int currentTime=480;//480 min=8:00, neka izpitut i ocenqvaneto sa v ramkite na 1 den

    public:
        Simulation(){
            enterData();
        }

        void enterData(){
            enterRoomData();
        }

        void enterRoomData(){
            std::cout<<"Please enter rows(N), columns(M), lector's lateness(L) and the minutes for grading each work(C): ";
            int N,M,L,C,count;
            std::cin>>N>>M>>L>>C;

            std::cout<<"Please enter the broken seats' count: ";
            std::cin>>count;
            int b[count];

            for (size_t i = 0; i < count; i++)
            {
                std::cin>>b[i];
            }

            this->room=Room(N,M,count,b);
            //this->room.printBrokenIndexes();
            this->room.printRoomSeats();            
            this->room.printRoomSeatsNulevo();//nulevo, zashtoto shte rabotia s drugite oznachenia,
            // no po tozi nachin shte izglejda napulnena zalata
        }
};

void startSimulation(){
    Simulation sim;
    std::cout<<std::endl;
}

int main(){
    startSimulation();
    return 0;
}
