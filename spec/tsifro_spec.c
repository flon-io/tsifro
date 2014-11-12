
//
// specifying tsifro
//
// Wed Nov 12 13:31:38 JST 2014
//

#include <errno.h>

#include "tsifro.h"


context "tsifro"
{
  describe "ftsi_generate_bc_salt()"
  {
    before each
    {
      char *s = NULL;
    }
    after each
    {
      free(s);
      errno = 0;
    }

    it "rejects work factors < 4"
    {
      s = ftsi_generate_bc_salt(1);

      expect(s == NULL);
      expect(errno i== EINVAL);
    }

    it "rejects work factors > 31"
    {
      s = ftsi_generate_bc_salt(33);

      expect(s == NULL);
      expect(errno i== EINVAL);
    }

    it "generates a salt"
    {
      s = ftsi_generate_bc_salt(14);

      expect(s ^== "$2a$14");
    }
  }
}

