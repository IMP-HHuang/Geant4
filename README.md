# Geant4

## Compile
  - cd bulid
  - cmake ..
  - make
## Run
  - 注意修改CMakeLists.txt中ROOT库的位置（ include_directories(/opt/ROOT/root_v6.16.00/include) ）
  - ./DSSD
  -  /run/beamOn Number
  -  exit(必须正常退出，否则root文件无法保存)
## [Forum](https://geant4-forum.web.cern.ch/) 
## [SourceCode](https://github.com/Geant4/geant4/tree/master/source/event/src)
## [Function](./Function/README.md)
## 一些模拟经验
  - G4UniformRand() 函数给的随机数是从随机数表中直接读取的，不改变CLHEP:HepRandom::setTheSeed(seed)的seed，每次获得的随机数是一样的，多个文件同时模拟的时候要注意。
  - 粒子直接发射到材料边界谁都不会管
  - new G4ParticleGun(n_particle)
    - 这里的n_particle是每个事件产生几个粒子，注意是相同的粒子，慎用！！！
  - Physics list
    - G4EmstandardPhysics_option4 : 580 MeV 以下的alpha粒子模拟时，不会考虑次级电子
  - step->GetTrack()->GetParentID()
    - Geant4版本不一样，ParentID会有区别，注意检查（别白跑了！！）
   - GPS重新设置放射源的位置
```cpp
  G4GeneralParticleSourceData* GPSData = G4GeneralParticleSourceData::Instance();
  G4SingleParticleSource* thisSrc = GPSData->GetCurrentSource(0);
  G4SPSPosDistribution* thisPosDis = thisSrc->GetPosDist();
  thisPosDis->SetCentreCoords(G4ThreeVector(Px, Py, Pz));
```
  - fParticleGun->GeneratePrimaryVertex(anEvent);
    - 这里只是把Gun的信息存下来，模拟的时候发射，不是直接在这发射的
    - 所有信息存完之后才会发射，不要想拿相同Event的上一个粒子的信息设置给下一个粒子的某个属性！！！（目前的想法是把多粒子发射放在不同的Event里来实现）
    - 发射的顺序是先存后发，即最后存入的粒子最先发射，模拟衰变的时候要注意！！！
