#include "Hospital.h"

#include <cassert>

std::ostream& operator<<(std::ostream& s, const EventResult& r)
{
    int enumIndex = (r.type < 0 || r.type > InvalidEvent) ? InvalidEvent : r.type;
    s << "Time[" << r.timePoint << "]: ";
    switch(enumIndex)
    {
        case DoctorQueueCheck:
            s << "Doctor(" << r.patientIdOrDoctorIndex
              << ") checked the patient queue." << std::endl;
            break;
        case RegistrationQueueEntrance:
            s << "Patient(" << r.patientIdOrDoctorIndex
              << ") " << "is registering." << std::endl;
            break;
        case RegistrationEnd:
            s << "Patient(" << r.patientIdOrDoctorIndex
              << ") registeration is complete." << std::endl;
            break;
        case ExaminationEnd:
            s << "Patient(" << r.patientIdOrDoctorIndex
              << ") examination is completed." << std::endl;
            break;
        case InvalidEvent:
        default:
            s << "Invalid Event!" << std::endl;
            break;
    }

    return s;
}

int Doctor::ExamTimeOf(const Patient& patient) const
{
    int n=patient.getPriority();
    int N=MAX_PATIENT_PRIORTIY;
    int t= baselineExaminationTime;
    int r=(N-n+1)*t;
    return r;
    // TODO: Implement
}


Hospital::Hospital(const Doctor& d0,
                   const Doctor& d1,
                   int rTime, int docTime)
    : currentTime(0)
    , registrationTime(rTime)
    , doctorCheckTime(docTime)
{
    doctors[0] = d0;
    doctors[1] = d1;
    patientsInExam[0] = NULL;
    patientsInExam[1] = NULL;
    
    eventQueue.InsertItem(new Event(currentTime + doctorCheckTime, DoctorQueueCheck, 0));
    eventQueue.InsertItem(new Event(currentTime + doctorCheckTime, DoctorQueueCheck, 1));
}

Hospital::~Hospital()
{
    while(!regQueue.IsEmpty()){
        Patient* patient=regQueue.Dequeue();
        delete patient;
    }
}

void Hospital::AddPatient(int id, int priority)
{   if((0 < priority || priority ==0) && (priority < MAX_PATIENT_PRIORTIY || priority == MAX_PATIENT_PRIORTIY)){
    Patient* added= new Patient(id, priority);
    regQueue.Enqueue(added);
    Event* newEvent=new Event(currentTime,RegistrationQueueEntrance,added);
    eventQueue.InsertItem(newEvent);
}
    // TODO: Implement
}

EventResult Hospital::DoSingleEventIteration()
{
    Event* deletedEvent = eventQueue.RemoveFirstItem();
    EventResult res;
    if(deletedEvent){
        currentTime = deletedEvent->getTimePoint();
        res.type=deletedEvent->getType();
        res.timePoint=currentTime;
        if(deletedEvent->getType()==RegistrationQueueEntrance ){
            res.patientIdOrDoctorIndex = deletedEvent->getPatient()->getId();
            Event* nEvent= new Event(currentTime+ registrationTime, RegistrationEnd, deletedEvent->getPatient());
            eventQueue.InsertItem(nEvent);
        }
        else if(deletedEvent->getType() == ExaminationEnd){
            res.patientIdOrDoctorIndex= deletedEvent->getPatient()->getId();
            int index;
            int patientId=deletedEvent->getPatient()->getId();
            if(patientsInExam[0] && patientsInExam[0]->getId()==patientId){
                index=0;
            }
            else{
                index=1;
            }
            delete deletedEvent->getPatient();
            patientsInExam[index]=NULL;
            if(examQueue.IsEmpty()){
                Event* mEvent= new Event(currentTime+ doctorCheckTime, DoctorQueueCheck, index);
                eventQueue.InsertItem(mEvent);
            }
            else{
                patientsInExam[index]=examQueue.RemoveFirstItem();
                Event* kEvent= new Event(currentTime+ doctors[index].ExamTimeOf(*patientsInExam[index]), ExaminationEnd, patientsInExam[index]);
                eventQueue.InsertItem(kEvent);
            }
        }
        else if(deletedEvent->getType() == DoctorQueueCheck){
            res.patientIdOrDoctorIndex = deletedEvent->getDoctorIndex();
            if(examQueue.IsEmpty()){
                Event* mEvent= new Event(currentTime+ doctorCheckTime, DoctorQueueCheck, deletedEvent->getDoctorIndex());
                eventQueue.InsertItem(mEvent);
            }
            else{
                int idx=deletedEvent->getDoctorIndex();
                patientsInExam[idx]=examQueue.RemoveFirstItem();
                Event* kEvent= new Event(currentTime+ doctors[idx].ExamTimeOf(*patientsInExam[idx]), ExaminationEnd, patientsInExam[idx]);
                eventQueue.InsertItem(kEvent);
            }
        }
        else if(deletedEvent->getType()==RegistrationEnd){
            res.patientIdOrDoctorIndex= deletedEvent->getPatient()->getId();
            examQueue.InsertItem(regQueue.Dequeue());
        }
        delete deletedEvent;
    }
    return res;
}