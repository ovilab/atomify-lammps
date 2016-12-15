#ifndef LAMMPSCONTROLLER_H
#define LAMMPSCONTROLLER_H
#include <memory>
#include <QVector>
#include <QString>
#include <QMap>
#include <mpi.h>
#include <lammps.h>
#include <fix.h>
#include <compute.h>
#include <modify.h>
#include <variable.h>
#include <error.h>
#include "parser/scriptcommand.h"
#include <lmptype.h>

void synchronizeLAMMPS_callback(void *caller, int mode, LAMMPS_NS::bigint ntimestep, int numberOfAtoms, LAMMPS_NS::tagint *tag, double **atom, double **force);

class LAMMPSController
{
private:
    LAMMPS_NS::LAMMPS *m_lammps = nullptr;
public:
    class System *system = nullptr;

    LAMMPSController();
    ~LAMMPSController();

    // Getters/setters
    bool didSynchronizeSimulator = false;
    QMutex *locker = nullptr;
    QString m_scriptFileName;
    QMap<QString, class SimulatorControl*> simulatorControls;
    bool paused = false;
    LAMMPS_NS::LAMMPS *lammps() const;
    bool tick();
    void stop();
    void start();

    void synchronizeLAMMPS();
    // LAMMPS internal access
    int findComputeId(QString identifier);
    int findVariableIndex(QString identifier);
    int findFixIndex(QString identifier);
    bool computeExists(QString identifier);
    bool fixExists(QString identifier);
    bool variableExists(QString identifier);
    bool groupExists(QString identifier);
    bool regionExists(QString identifier);
    double variableValue(QString identifier);
    LAMMPS_NS::Compute *findComputeByIdentifier(QString identifier);
    LAMMPS_NS::Fix *findFixByIdentifier(QString identifier);
};

#endif // LAMMPSCONTROLLER_H
