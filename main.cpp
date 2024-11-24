#include <iostream>

class Seat{
    private:
        int index;//za poveche udobstvo
        char type;//Occupied, Free ili Broken, ama shte dobavq i edin da ne se zaema - N
        bool occupied=false;
        //Student student;//koi student v momenta e zael mqstoto
        int timeUsed=0;//kolko vreme dosega e sedql studentut

    public:
    Seat(){}
        Seat(int i, char t, bool oc):index(i), type(t), occupied(oc){}
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
        Seat* seats=nullptr;
    
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
                    char seat=seats[index].getType();
                    std::cout << seat << " ";
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
        /*std::queue<Student> waiting;
        int currentTime=8;
        Seat* seats;
        Seat* usableSeats;*/

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
