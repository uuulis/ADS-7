// Copyright 2022 NNTU-CS
#include <iostream>
#include <fstream>
#include <random>
#include "train.h"

int main() {
    std::ofstream out("result/data.csv");
    out << "n,all_off,all_on,random" << std::endl;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);
    
    for (int n = 2; n <= 500; n += 10) {
        long long ops_off = 0, ops_on = 0, ops_rand = 0;
        
        for (int trial = 0; trial < 10; trial++) {
            Train train_off;
            for (int i = 0; i < n; i++) train_off.addCar(false);
            train_off.getLength();
            ops_off += train_off.getOpCount();
            
            Train train_on;
            for (int i = 0; i < n; i++) train_on.addCar(true);
            train_on.getLength();
            ops_on += train_on.getOpCount();
            
            Train train_rand;
            for (int i = 0; i < n; i++) train_rand.addCar(dis(gen));
            train_rand.getLength();
            ops_rand += train_rand.getOpCount();
        }
        
        out << n << "," << ops_off/10 << "," << ops_on/10 << "," << ops_rand/10 << std::endl;
    }
    out.close();
    
    std::ofstream script("result/plot.py");
    script << "import matplotlib.pyplot as plt\n"
           << "import numpy as np\n"
           << "data=np.loadtxt('result/data.csv',delimiter=',',skiprows=1)\n"
           << "n=data[:,0];off=data[:,1];on=data[:,2];rand=data[:,3]\n"
           << "plt.figure(figsize=(10,6))\n"
           << "plt.scatter(n,off,s=8,label='All off')\n"
           << "plt.scatter(n,on,s=8,label='All on')\n"
           << "plt.scatter(n,rand,s=8,label='Random')\n"
           << "zoff=np.polyfit(n,off,2);poff=np.poly1d(zoff)\n"
           << "zon=np.polyfit(n,on,2);pon=np.poly1d(zon)\n"
           << "zrand=np.polyfit(n,rand,2);prand=np.poly1d(zrand)\n"
           << "plt.plot(n,poff(n),'--',label='Trend off')\n"
           << "plt.plot(n,pon(n),'--',label='Trend on')\n"
           << "plt.plot(n,prand(n),'--',label='Trend random')\n"
           << "plt.xlabel('Train length n')\n"
           << "plt.ylabel('Number of operations')\n"
           << "plt.title('Operations vs Train Length')\n"
           << "plt.legend();plt.grid(True)\n"
           << "plt.savefig('result/plot.png',dpi=150)\n"
           << "plt.close()\n";
    script.close();
    
    if (system("python result/plot.py") == -1) {
        std::cout << "Warning: Could not run plot script" << std::endl;
    }
    std::cout << "Done. Plot saved to result/plot.png" << std::endl;
    
    return 0;
}
