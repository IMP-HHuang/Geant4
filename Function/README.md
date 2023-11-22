# GetTime
  - Local time (the time in track) : step->GetPreStepPoint()->GetLocalTime()
  - Global time (the time in event) : step->GetPreStepPoint()->GetGlobalTime() 

# GetParentId
  - step->GetTrack()->GetParentID()
    - primary particle : return 0
    - Secondary particle : retuen (>1 value)   
