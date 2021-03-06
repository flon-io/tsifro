
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
      s = ftsi_generate_bc_salt(NULL, 1);

      expect(s == NULL);
      expect(errno i== EINVAL);
    }

    it "rejects work factors > 31"
    {
      s = ftsi_generate_bc_salt(NULL, 33);

      expect(s == NULL);
      expect(errno i== EINVAL);
    }

    it "generates a salt"
    {
      s = ftsi_generate_bc_salt(NULL, 14);

      expect(s ^== "$2a$14");
    }

    it "accepts a different scheme"
    {
      s = ftsi_generate_bc_salt("$2b$", 13);

      expect(s ^== "$2b$13");
    }
  }

  describe "ftsi_bc_hash()"
  {
    it "hashes strings"
    {
      char *salt = ftsi_generate_bc_salt(NULL, 10);

      char *h0 = ftsi_bc_hash("toto nada", salt);
      char *h1 = ftsi_bc_hash("toto nada", h0);

      expect(h0 === h1);
      //ret = bcrypt_hashpw("thepassword", "expectedhash", outhash);

      free(salt); free(h0); free(h1);
    }
  }

  describe "ftsi_bc_verify()"
  {
    before each
    {
      char *salt = ftsi_generate_bc_salt(NULL, 10);
      char *hash = ftsi_bc_hash("heavy rotation", salt);
    }
    after each
    {
      free(salt);
      free(hash);
    }

    it "returns 1 if the pass matches"
    {
      expect(ftsi_bc_verify("heavy rotation", hash) i== 1);
    }

    it "returns 0 else"
    {
      expect(ftsi_bc_verify("light rotation", hash) i== 0);
    }

    it "verifies 'wyvern'"
    {
      expect(
        ftsi_bc_verify(
          "wyvern",
          "$2a$07$hi1ZGrPNfHAX/a5p0oTu0edFxY3aCZBK.NfIx9RrIEPWaiidMV8ty"
        ) i== 1);
    }
  }
}

