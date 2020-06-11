// Copyright(C) 1999-2020 National Technology & Engineering Solutions
// of Sandia, LLC (NTESS).  Under the terms of Contract DE-NA0003525 with
// NTESS, the U.S. Government retains certain rights in this software.
// 
// See packages/seacas/LICENSE for details

#ifndef IOSS_Iotr_Offset3D_h
#define IOSS_Iotr_Offset3D_h

#include "Ioss_VariableType.h" // for VariableType
#include <Ioss_Transform.h>    // for Transform, Factory
#include <string>              // for string
#include <vector>              // for vector
namespace Ioss {
  class Field;
} // namespace Ioss

namespace Iotr {

  class Offset3D_Factory : public Factory
  {
  public:
    static const Offset3D_Factory *factory();

  private:
    Offset3D_Factory();
    Ioss::Transform *make(const std::string & /*unused*/) const override;
  };

  class Offset3D : public Ioss::Transform
  {
    friend class Offset3D_Factory;

  public:
    const Ioss::VariableType *output_storage(const Ioss::VariableType *in) const override;
    int                       output_count(int in) const override;

    void set_properties(const std::string &name, const std::vector<int> &values) override;
    void set_properties(const std::string &name, const std::vector<double> &values) override;

  protected:
    Offset3D();

    bool internal_execute(const Ioss::Field &field, void *data) override;

  private:
    int    intOffset[3]{};
    double realOffset[3]{};
  };
} // namespace Iotr

#endif // IOSS_Iotr_Offset3D_h
