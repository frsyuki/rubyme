# @RUBYME_MK@
rubyme$(EXEEXT): $(PROGRAM) rubyme.$(OBJEXT)
	$(Q) $(PURIFY) $(CC) $(LDFLAGS) $(XLDFLAGS) $(MAINLIBS) rubyme.$(OBJEXT) $(EXTOBJS) $(LIBRUBYARG) $(LIBS) $(OUTFLAG)$@

