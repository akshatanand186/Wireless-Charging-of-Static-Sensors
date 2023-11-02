#include <bits/stdc++.h>
#define debug(n) cout << #n << " : " << n ; 
#define debug2(n1,n2) cout << #n1 << " : " << n1 << "  " << #n2 << " : " << n2 << '\n';
#define debug3(n1,n2,n3) cout << #n1 << " : " << n1 << "  " << #n2 << " : " << n2 << "  " << #n3 << " : " << n3 << '\n';

using namespace std;

int debugvar = 1;

class Point{
    public:
    double x,y;
    Point(){}
    Point(double X, double Y){
        x = X, y = Y;
    }
    void printPoint(){
        if(debugvar)
        cout << "x: " << x << " y: " << y ;
        else cout << x << " " << y ;
    }
};

class StaticSensor{
    public:
        double x,y,z,battery_capacity;
        double state_of_charge;
        Point P;
        double charging_rate, discharging_rate;
        double deadline;
        StaticSensor(double X, double Y, double B, double soc, double cr, double dr){
            x = X, y = Y, battery_capacity = B, state_of_charge = soc, charging_rate = cr, discharging_rate = dr;
            z = x*x + y*y;
            P.x = x;
            P.y = y;
            deadline = battery_capacity*state_of_charge/discharging_rate;
        }
};


double distance(Point p1, Point p2){
    return sqrt(double(p1.x-p2.x)*double(p1.x - p2.x)  + double(p1.y-p2.y)*double(p1.y-p2.y));
}
Point midPoint(Point p1, Point p2){
    Point p3((p1.x+p2.x)/2,(p1.y+p2.y)/2);
    return p3;
}
class Triangle{
    public:
    Point p1,p2,p3;
    double a,b,c;
    double AreaofTriangle;
    double circumRadius;
    Point circumcenter;
    double distance(Point p1, Point p2){
        return sqrt(double(p1.x-p2.x)*double(p1.x - p2.x)  + double(p1.y-p2.y)*double(p1.y-p2.y));
    }
    bool calculateCircumcenter(){
        double d = 2 * (p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y));
        if (d == 0) {
            return false;  // Collinear points; no circumcenter exists
        }

        double ux = ((p1.x * p1.x + p1.y * p1.y) * (p2.y - p3.y) + (p2.x * p2.x + p2.y * p2.y) * (p3.y - p1.y) + (p3.x * p3.x + p3.y * p3.y) * (p1.y - p2.y)) / d;
        double uy = ((p1.x * p1.x + p1.y * p1.y) * (p3.x - p2.x) + (p2.x * p2.x + p2.y * p2.y) * (p1.x - p3.x) + (p3.x * p3.x + p3.y * p3.y) * (p2.x - p1.x)) / d;
        circumcenter.x = ux;
        circumcenter.y = uy;
        return true;
    }
    Triangle(Point x1,Point x2, Point x3){
        p1 = x1, p2 = x2, p3 = x3;
        a = distance(x2,x3);
        b = distance(x1,x3);
        c = distance(x1,x2);
        double s = ((double)(a+b+c))/2;
        AreaofTriangle = sqrt((s*(s-a)*(s-b)*(s-c)));
        circumRadius = double(a*b*c)/(4*AreaofTriangle);
        calculateCircumcenter();
    }  
    void printTriangle(){
        cout << "Vertex 1 ";
        p1.printPoint();
        cout << endl;
        cout << "Vertex 2 ";
        p2.printPoint();
        cout << endl;
        cout << "Vertex 3 ";
        p3.printPoint();
        cout << endl;
    }
};


class SoujournLocationWithWeights{
    public:
        double value;
        vector<int> SLs;
        Point coordinate;
    SoujournLocationWithWeights(Point P){
        coordinate = P;
        value = 0;
    }
};

bool cmp(const Triangle &t1, const Triangle &t2){
    return t1.circumRadius < t2.circumRadius;
}
bool CMPBYDEADLINE(const SoujournLocationWithWeights &a, const SoujournLocationWithWeights &b){
    return a.value > b.value; 
}

void takeInput(string printMessage, int &Number){
    cout << printMessage << endl;
    cin >> Number;
}


vector<Triangle> getDelanauyTriangles(vector<StaticSensor> listofSS){
    int n = listofSS.size();
    vector<double> x(n);
    vector<double> y(n);
    vector<double> z(n);
    for(int i=0;i<n;i++){
        x[i] = listofSS[i].x;
        y[i] = listofSS[i].y;
        z[i] = listofSS[i].z;
    }
    vector<Triangle> answer;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            // bool value = false;
            for(int k=i+1;k<n;k++){
                if(j==k) continue;
                double xn = (y[j] - y[i]) * (z[k] - z[i]) - (y[k] - y[i]) * (z[j] - z[i]);
                double yn = (x[k] - x[i]) * (z[j] - z[i]) - (x[j] - x[i]) * (z[k] - z[i]);
                double zn = (x[j] - x[i]) * (y[k] - y[i]) - (x[k] - x[i]) * (y[j] - y[i]);
                int flag;
                if(zn < 0)
                    flag = 1;
                else
                    flag = 0;
                if(flag == 1)
                    for(int m = 0; m < n; m++)
                        flag = flag && ((x[m] - x[i]) * xn + (y[m] - y[i]) * yn + (z[m] - z[i]) * zn <= 0);
                if(flag == 1){
                    Point t1(x[i],y[i]);
                    Point t2(x[j],y[j]);
                    Point t3(x[k],y[k]);
                    Triangle t(t1,t2,t3);
                    answer.push_back(t);
                    // value = true; break;
                }
            }
            // if(value) break;
        }
    }
    return answer;
}


class WirelessChargingVehicle{
    public:
    double speedOfWCV;
    double chargingRange;
    double constantofCharging;
    double totalCharge;
    Point initialLocation;
    Point currentLocation;
    vector<Point> SLvisited;
    vector<int> SSvisited;
    WirelessChargingVehicle(double sp, double ch, double constofCharge, double totalC, Point ini){
        speedOfWCV = sp;
        chargingRange = ch;
        constantofCharging = constofCharge;
        totalCharge = totalC;
        initialLocation = ini;
    }
    void printVehiclesRoutes(){
        if(debugvar) cout << "Vehicles route: \n";
        initialLocation.printPoint();
        cout << endl;
        for(auto t:SLvisited){
            t.printPoint();
            cout << endl;
        }
        if(debugvar) cout << "SS visited ";
        for(auto t:SSvisited) cout << t << " "; 
        cout << endl;
    }

};

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    // cout << fixed << setprecision(5);
    // debugvar = 0;
    int staticSensorsCount; 
    cin >> staticSensorsCount;
    // takeInput("Enter the number of static sensors: ",staticSensorsCount);
    double chargingRange; cin >> chargingRange;
    vector<StaticSensor> listOfSS;


    map<pair<double,double>,int> mapping; // Stores which point (x,y) is marked to which static sensor number - i+1
    map<pair<double,double>,int> SLforpoint;
    for(int i=0;i<staticSensorsCount;i++){
        // cout << "Enter the x,y coordinate, battery_capacity, state of charge, charging rate, discharging rate for - " << i << " SS\n";
        double X,Y,B;
        double soc, cr, dr;
        cin >> X >> Y >> B;
        mapping[{X,Y}] = i+1;
        cin >> soc >> cr >> dr;
        listOfSS.push_back(StaticSensor(X,Y,B,soc,cr,dr));
    }

    vector<Triangle> answer = getDelanauyTriangles(listOfSS);
    for(auto t:answer){
        t.printTriangle();
    }
    sort(answer.begin(),answer.end(),cmp);
    // Sort the delanauy triangles according to their circumradius
    set<int> coveredPoints;
    vector<Triangle> possibleSoujourn;
    vector<Point> possibleSoujournLocations;
    int start = 0;
    for(int i=0;i<answer.size();i++){
        int cnt = 0;
        // Debug Statements
        answer[i].printTriangle();
        answer[i].circumcenter.printPoint();
        cout << endl;
        cout << answer[i].circumRadius << endl;

        for(int j=0;j<staticSensorsCount;j++){
            if(coveredPoints.count(j)) continue;
            // debug(j);
            // listOfSS[j].P.printPoint();
            // answer[i].circumcenter.printPoint();
            // answer[i].printTriangle();
            // cout << endl;
            double dist = distance(listOfSS[j].P,answer[i].circumcenter);
            // debug2(j,dist);
            if(dist<=chargingRange){
                cnt++;
                coveredPoints.insert(j);
                SLforpoint[{listOfSS[j].x,listOfSS[j].y}] = possibleSoujournLocations.size();
            }
        }
        if(cnt) possibleSoujourn.push_back(answer[i]), start = i+1, possibleSoujournLocations.push_back(answer[i].circumcenter);
    }
    cout << "Possible Soujourn: \n";
    for(auto t:possibleSoujourn){
        t.circumcenter.printPoint();
        cout << endl;
    }
    for(auto t:coveredPoints) cout << t << endl;
    for(int i=start;i<answer.size();i++){
        int x1 = coveredPoints.count(mapping[{answer[i].p1.x,answer[i].p1.y}]-1);
        int x2 = coveredPoints.count(mapping[{answer[i].p2.x,answer[i].p2.y}]-1);
        int x3 = coveredPoints.count(mapping[{answer[i].p3.x,answer[i].p3.y}]-1);
        if(!x2 && !x3){
            Point mid = midPoint(answer[i].p2,answer[i].p3);
            double dist = distance(mid,answer[i].p2);
            if(dist<=chargingRange){

                SLforpoint[{answer[i].p2.x,answer[i].p2.y}] = possibleSoujournLocations.size();
                SLforpoint[{answer[i].p3.x,answer[i].p3.y}] = possibleSoujournLocations.size();
                
                possibleSoujournLocations.push_back(mid);
                coveredPoints.insert(mapping[{answer[i].p2.x,answer[i].p2.y}]-1);
                coveredPoints.insert(mapping[{answer[i].p3.x,answer[i].p3.y}]-1);
            }
        }
        x1 = coveredPoints.count(mapping[{answer[i].p1.x,answer[i].p1.y}]-1);
        x2 = coveredPoints.count(mapping[{answer[i].p2.x,answer[i].p2.y}]-1);
        x3 = coveredPoints.count(mapping[{answer[i].p3.x,answer[i].p3.y}]-1);
        if((!x1 && !x3)){
            Point mid = midPoint(answer[i].p3,answer[i].p1);
            double dist = distance(mid,answer[i].p3);
            if(dist<=chargingRange){
                
                SLforpoint[{answer[i].p1.x,answer[i].p1.y}] = possibleSoujournLocations.size();
                SLforpoint[{answer[i].p3.x,answer[i].p3.y}] = possibleSoujournLocations.size();

                possibleSoujournLocations.push_back(mid);
                coveredPoints.insert(mapping[{answer[i].p3.x,answer[i].p3.y}]-1);
                coveredPoints.insert(mapping[{answer[i].p1.x,answer[i].p1.y}]-1);
            }
            continue;
        }
        x1 = coveredPoints.count(mapping[{answer[i].p1.x,answer[i].p1.y}]-1);
        x2 = coveredPoints.count(mapping[{answer[i].p2.x,answer[i].p2.y}]-1);
        x3 = coveredPoints.count(mapping[{answer[i].p3.x,answer[i].p3.y}]-1);
        if(!x1 && !x2){
            Point mid = midPoint(answer[i].p1,answer[i].p2);
            double dist = distance(mid,answer[i].p1);
            if(dist<=chargingRange){

                SLforpoint[{answer[i].p1.x,answer[i].p1.y}] = possibleSoujournLocations.size();
                SLforpoint[{answer[i].p2.x,answer[i].p2.y}] = possibleSoujournLocations.size();
                
                possibleSoujournLocations.push_back(mid);
                coveredPoints.insert(mapping[{answer[i].p1.x,answer[i].p1.y}]-1);
                coveredPoints.insert(mapping[{answer[i].p2.x,answer[i].p2.y}]-1);
            }
            continue;
        }
        debug2(i,i);
    }
    for(int i=0;i<staticSensorsCount;i++){
        if(coveredPoints.count(i)) continue;
        coveredPoints.insert(i);
        SLforpoint[{listOfSS[i].x,listOfSS[i].y}] = possibleSoujournLocations.size();
        possibleSoujournLocations.push_back(listOfSS[i].P);
    }

    for(auto t:possibleSoujournLocations){
        t.printPoint();
        cout << endl;
    }


    /*
    --Section of WCVs - parameters like coordinates of Base Station(same for all), constantofCharging, totalCharge
    Efficiency constant 
    */
    double speedOfWCV,constantofCharging,totalCharge;
    Point BaseStation;
    cin >> speedOfWCV >> constantofCharging >> totalCharge;
    cin >> BaseStation.x >> BaseStation.y;

    
    vector<SoujournLocationWithWeights> weightedPossibleSLS;
    for(auto t:possibleSoujournLocations){
        weightedPossibleSLS.push_back(SoujournLocationWithWeights(t));
    }
    for(int i=0;i<listOfSS.size();i++){
        Point pt = listOfSS[i].P;
        int SL = SLforpoint[{pt.x,pt.y}];
        debug2(i,SL);
        weightedPossibleSLS[SL].value += 1/(listOfSS[i].deadline*listOfSS[i].deadline);
        weightedPossibleSLS[SL].SLs.push_back(i);
        // Custom functions added for priority
        // More weight.first means more priority, as deadline is approaching
    }
    
    sort(weightedPossibleSLS.begin(),weightedPossibleSLS.end(),CMPBYDEADLINE);

    for(auto t:weightedPossibleSLS){
        cout << "Weight : ";
        cout << t.value << " ";
        cout << "| Points : ";
        for(auto x:t.SLs) cout << x << " deadline: " << listOfSS[x].deadline << " ";
        // for(auto x:t.SLs) cout <<  << " ";
        cout << "| ";
        t.coordinate.printPoint();
        cout << endl;
    }


    vector<WirelessChargingVehicle> vehicles;
    WirelessChargingVehicle currentWCVVehicle = WirelessChargingVehicle(speedOfWCV,chargingRange,constantofCharging,totalCharge,BaseStation);

    double currentTime = 0;
    Point LastLocation = BaseStation;
    bool notPossible = 0;
    for(auto t:weightedPossibleSLS){
        double timeTakenToReachCurrentSL = distance(LastLocation,t.coordinate)/speedOfWCV;
        debug2(currentTime,timeTakenToReachCurrentSL);
        vector<int> NotReachable;
        bool flag = 0;
        for(int id:t.SLs){
            double deadline = listOfSS[id].deadline;
            if(deadline<currentTime+timeTakenToReachCurrentSL){
                NotReachable.push_back(id); 
            }
            else{
                // debug3(deadline,currentTime,timeTakenToReachCurrentSL);
                currentWCVVehicle.SSvisited.push_back(id);
                flag = 1;
            }
        }
        if(flag){
            currentWCVVehicle.SLvisited.push_back(t.coordinate);
        }
        if(!NotReachable.empty()){ // Make a New WCV directly reaching from Base Station 
            vehicles.push_back(currentWCVVehicle);
            currentWCVVehicle = WirelessChargingVehicle(speedOfWCV,chargingRange,constantofCharging,totalCharge,BaseStation);
            double timeTakenToReachThisSL = distance(BaseStation,t.coordinate)/speedOfWCV;
            for(int id:NotReachable){
                double deadline = listOfSS[id].deadline;
                if(deadline<timeTakenToReachThisSL){
                    notPossible = 1;
                    cout << "NOT POSSIBLE\n";
                    return 0;
                }
                else{
                    currentWCVVehicle.SSvisited.push_back(id);
                }
            }
            currentWCVVehicle.SLvisited.push_back(t.coordinate);
            LastLocation = t.coordinate;
            currentTime = timeTakenToReachThisSL; // add the time taken to charge the Points 
        }
        else{
            LastLocation = t.coordinate;
            currentTime += timeTakenToReachCurrentSL;
        }
        debug(currentTime);
        cout << endl;
    }
    vehicles.push_back(currentWCVVehicle);
    for(auto t:vehicles){
        t.printVehiclesRoutes();
    }


}