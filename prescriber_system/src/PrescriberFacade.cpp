#include <PrescriberFacade.hpp>
#include <Database.hpp>
#include <Prescriber.hpp>
#include "utils.h"
#include <SaveCsv.hpp>
#include <SaveJson.hpp>
#include <Patient.hpp>

PrescriberFacade::PrescriberFacade(Database* database, Prescriber* prescriber,
                                    std::string rulepath, std::string json)
{
    SetDataBase(database);
    SetPrescriber(prescriber);

    database->parser(json);
    prescriber->parser(rulepath);
}

void PrescriberFacade::diagnosis(std::string id, std::string symtoms, int saveOpt, std::string outputpath)
{
    prescriber->diagnosis(id, symtoms);

    if (saveOpt && SAVE_AS_CSV) {
        std::cout << "The diagnosis result is save as CSV and path at:" << outputpath << std::endl;
        prescriber->SetStrategy(new SaveCsv());
        Patient* patient = database->GetPatientByid(id);
        prescriber->save(outputpath, patient);
    }

    if (saveOpt && SAVE_AS_JSON) {
        std::cout << "The diagnosis result is save as Json and path at:" << outputpath << std::endl;
        prescriber->SetStrategy(new SaveJson());
        Patient* patient = database->GetPatientByid(id);
        prescriber->save(outputpath, patient);
    }

}

Database* PrescriberFacade::GetDataBase()
{
    return database;
}

Prescriber* PrescriberFacade::GetPrescriber()
{
    return prescriber;
}

void PrescriberFacade::SetDataBase(Database* database)
{
    utils::RequireNonNull(database);
    this->database = database;
}

void PrescriberFacade::SetPrescriber(Prescriber* prescriber)
{
    utils::RequireNonNull(prescriber);
    this->prescriber = prescriber;
}

PrescriberFacade::~PrescriberFacade()
{
}