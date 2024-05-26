#include <DiagnosticRules.hpp>
#include <Prescription.hpp>

DiagnosticRules::DiagnosticRules(std::string disease, Prescription* prescription)
{
    SetDisease(disease);
    SetPrescription(prescription);
}

std::vector<DiagnosticRules*> DiagnosticRules::defaultrules()
{
    DiagnosticRules* rule1 = new DiagnosticRules(
        "打噴嚏,頭痛,咳嗽",
        new Prescription(
            "清冠一號",
            "新冠肺炎(專業學名:COVID-19)",
            "清冠一號",
            "將相關藥材裝入茶包裡,使用500 mL 溫、熱水沖泡悶煮1~3 分鐘後即可飲用。"
        )
    );

    DiagnosticRules* rule2 = new DiagnosticRules(
        "打噴嚏,18female",
        new Prescription(
            "青春抑制劑",
            "有人想你了 (專業學名:Attractive)",
            "假鬢角、臭味",
            "把假鬢角黏在臉的兩側，讓自己異性緣差一點，自然就不會有人想妳了。"
        )
    );

    DiagnosticRules* rule3 = new DiagnosticRules(
        "BMI>26.0,打呼",
        new Prescription(
            "打呼抑制劑",
            "睡眠呼吸中止症(專業學名:SleepApneaSyndrome)",
            "一捲膠帶",
            "睡覺時，撕下兩塊膠帶，將兩塊膠帶交錯黏在關閉的嘴巴上，就不會打呼了。"
        )
    );

    std::vector<DiagnosticRules*> rules = std::vector<DiagnosticRules*>();
    rules.push_back(rule1);
    rules.push_back(rule2);
    rules.push_back(rule3);

    return rules;
}

std::string DiagnosticRules::GetDisease()
{
    return disease;
}

Prescription* DiagnosticRules::GetPrescription()
{
    return prescription;
}

void DiagnosticRules::SetDisease(std::string disease)
{
    this->disease = disease;
}

void DiagnosticRules::SetPrescription(Prescription* prescription)
{
    utils::RequireNonNull(prescription);
    this->prescription = prescription;
}

DiagnosticRules::~DiagnosticRules()
{
}