# GetTime
  - Local time (the time in track) : step->GetPreStepPoint()->GetLocalTime()
  - Global time (the time in event) : step->GetPreStepPoint()->GetGlobalTime() 

# GetParentId (获取粒子级数)
  - step->GetTrack()->GetParentID()
    - primary particle （Mother） : return 0
    - Secondary particle : retuen (>1 value)
    - Daughter ：return 1
    - Granddaughter : return 2
    - ......   
