#define DECLARE_COLOURSCHEME(name) static const char* name[][3]

DECLARE_COLOURSCHEME(black_and_white) = {
	[SchemeNorm] = { "#ffffff", "#000000", "#000000" },
	[SchemeSel]  = { "#000000", "#ffffff", "#ffffff" }, 
	[SchemeOut]  = { "#000000", "#ffffff", "#ffffff" }, 
};

#define colors black_and_white
