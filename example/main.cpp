#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cmath>

int main(){
    return 0;
}

// const int MAX_drop = 3;

// // point struct
// struct Point {
//     double x;
//     double y;
//     double z;

//     double prevX;
//     double prevY;
//     double prevZ;

//     double dx;
//     double dy;
//     double dz;
    
//     double missingCounter;
//     bool estimated = false;
    
//     double id;
// };

// // vector of points
// std::vector<Point> Points;

// // make a point and add it to Points
// void makePoint(double x, double y, double z, double spd, double id) {
//     Point p;
    
//     p.x = x;
//     p.y = y;
//     p.z = z;

//     p.prevX = x;
//     p.prevY = y;
//     p.prevZ = z;
    
//     p.dx = 0;
//     p.dy = 0;
//     p.dz = 0;
    
//     p.missingCounter = 0;
    
//     p.estimated = false;

//     p.id = id;
//     // add it to the list of points
//     Points.push_back(p);
// }

// bool checkPts(Point &pt, std::vector<double> listIDs){
//     // check if the PointID exists in the listIDs
//     if (std::find(listIDs.begin(), listIDs.end(), pt.id) != listIDs.end()) {
//         pt.missingCounter = 0;
//         return true;
//     } else {
//         pt.missingCounter++;
//         return false;
//     }
// }

// void estimate(Point &pt) {
//     if(!pt.estimated){
//         // first time
//         pt.dx = (pt.x - pt.prevX);
//         pt.dy = (pt.y - pt.prevY);
//         pt.dz = (pt.z - pt.prevZ);
//     }
//     if (pt.missingCounter <= MAX_drop) {
//         // if both are missing keep the speed
//         pt.x = pt.x + pt.dx;
//         pt.y = pt.y + pt.dy;
//         pt.z = pt.z + pt.dz;
        
//         pt.prevX = pt.x;
//         pt.prevY = pt.y;
//         pt.prevZ = pt.z;
//     }
//     pt.estimated = true;
    
// }

// int main() {
//     // Example input vectors
//     std::vector<double> ptr1 = {1.0, 2.0 ,std::numeric_limits<double>::quiet_NaN(),4.0, std::numeric_limits<double>::quiet_NaN(), 5.0};
//     std::vector<double> ptr2 = {10.0, 9.0, 8.0, std::numeric_limits<double>::quiet_NaN(),7.0 ,6.0};

//     makePoint(1.0, 2.0, 3.0, 0.0, 1.0);
//     makePoint(10.0, 9.0, 8.0, 0.0, 2.0);
    
//     std::vector<double> listIDs = {1,2,4,5};
    
//     int dataSize = ptr1.size();

//     for (int i = 0; i < dataSize; ++i) {
//         double ptr1_val = ptr1[i];
//         double ptr2_val = ptr2[i];
//         // fake change IDs
//         listIDs[0] = 1;
//         listIDs[1] = 2;
//         if (std::isnan(ptr1_val)){
//             listIDs[0] = 21;
//         }
//         if (std::isnan(ptr2_val)){
//             listIDs[1] = 20;
//         }
        
//         // check if the point is in the list of IDs
//         for(auto &pt : Points)
//         {
//             if(checkPts(pt,listIDs))
//             {   
//                 pt.estimated = 0;
//                 if(pt.id == 1){ //need to implement this for ROS later
//                 pt.prevX = pt.x;
//                 pt.x = ptr1_val;
//                 }
//                 if(pt.id == 2){
//                 pt.prevX = pt.x;
//                 pt.x = ptr2_val;
//                 } 
//             }else{
//                 estimate(pt);
//             }
//         }
      
//         // Display the results
//         std::cout << "listIDs: [" <<  listIDs[0] << ","<< listIDs[1] <<"," <<  listIDs[2] << "," <<  listIDs[3] << "]\n";
//         std::cout << "#" << i + 1 << "\n";
//         std::cout << "inputs :\t(" << ptr1_val << "\t , \t" << ptr2_val <<")\n";
//         std::cout << "outputs:\t(" << Points[0].x << "\t , \t" << Points[1].x << ")\n";
//         std::cout << "IDS    :\t("<< Points[0].id << "\t , \t"<< Points[1].id<<")\n";
//         std::cout << "missing#:\t("<<Points[0].missingCounter << "\t , \t"<< Points[1].missingCounter<<")\n";
//         std::cout << "estimated:\t("<< Points[0].estimated << "\t , \t"<< Points[1].estimated <<")\n";
//         std::cout << "----------------------------------------\n";
//     }

//     return 0;
// }