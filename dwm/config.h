/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int smartgaps = 1;
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
//static const unsigned int gappx     = 12;        /* gap pixel between windows */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "SauceCodePro Nerd Font:size=12" };
static const char dmenufont[]       = "SauceCodePro Nerd Font:size=12";
static const unsigned int baralpha  = 0xd0;     /* Transparency for status bar */
static const unsigned int borderalp = 0xcc;     /* Transparency for the borders */
static const char col_gray1[]       = "#2E344F";
static const char col_gray2[]       = "#3B4252";
static const char col_gray3[]       = "#D8DEE9";
static const char col_gray4[]       = "#E5E9F0";
static const char col_cyan[]        = "#81A1C1";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan },
};
static const unsigned int alphas[][3] = {
	/*               fg         bg         border   */
        [SchemeNorm] = { OPAQUE, baralpha, borderalp },
        [SchemeSel]  = { OPAQUE, baralpha, borderalp },
};
/* tagging */
static const char *tags[] = { "", "󱓩", "", "󰛓", "󰏆", "󰾔", ""};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      		instance    	title       	tags mask     	isfloating   monitor */
	{ "Gimp",     		NULL,       	NULL,       	0,            	1,           	-1 },
	{ "qutebrowser",  	NULL,       	NULL,       	1 << 5,       	0,           	-1 },
	{ "midori",		NULL,		NULL,		1 << 5,		0,		-1 },
	{ "epiphany",		NULL, 		NULL,		1 << 5,		0,		-1 },
	{ "feh",      		NULL,	  	NULL,	    	0,            	1,        	-1 },
	{ "thunar",  		NULL,       	NULL,       	0,            	0,       	-1 },
	{ "libreoffice",        NULL,           NULL,       	1 << 4,         0,              -1 },
        { "libreoffice-writer", NULL,           NULL,           1 << 4,         0,              -1 },
        { "FeatherPad",         NULL,           NULL,           1 << 3,         0,              -1 },
//      { "Gnome-terminal",     NULL,           NULL,           1 << 2,         0,              -1 },
	{ "Geany",		NULL,		NULL,		1 << 2,		0,		-1 },
        { "st",                 NULL,           NULL,           0,              0,              -1 },
        { "obsidian",           NULL,           NULL,           1 << 1,         0,              -1 },
//	{ "konsole", 		NULL, 		NULL,		1 << 2, 	0,		-1 },
	{ "codeblocks",		NULL,		NULL,		1 << 2,		0,		-1 },
	{ "QtCreator",		NULL,		NULL,		1 << 6,		0,		-1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "->󰬛",      tile },    /* first entry is default */
	{ "->󰬍",      NULL },    /* no layout function means floating behavior */
	{ "->󰬔",      monocle },
	{ "->󰬊",      centeredmaster },
	{ "->󰬊 󰬍",    centeredfloatingmaster },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "rofi", "-show", "drun", NULL };
static const char *termcmd[]  = { "konsole", NULL };
static const char *filecmd[]  = { "rofi", "-show", "filebrowser", NULL };
// static const char *nvimcmd[]  = { "konsole", NULL };
static const char *nordcmd[]  = { "nordic", NULL };

#include "movestack.c"
static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_x,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_r,      spawn,          {.v = nordcmd } },
//	{ MODKEY,                       XK_n,      spawn,          {.v = nvimcmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ ControlMask|ShiftMask,        XK_j,      rotatestack,    {.i = +1 } },
        { ControlMask|ShiftMask,        XK_k,      rotatestack,    {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_r,      resizemouse,    {0} },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_o,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
//	TAGKEYS(                        XK_8,                      7)
//	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY|ShiftMask,             XK_Tab,    toggleAttachBelow, {0} },
	{ MODKEY,                       XK_equal,  incrgaps,       {.i = +1 } },
	{ MODKEY,                       XK_minus,  incrgaps,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_equal,  incrogaps,      {.i = +2 } },
	{ MODKEY|ShiftMask,             XK_minus,  incrogaps,      {.i = -2 } },
	// Poweroff script
	{ MODKEY,                       XK_z,      spawn,          SHCMD("powerrofi") },
	// Wifi Menu
	{ MODKEY,                       XK_w,      spawn,          SHCMD("wifirofi") },
	// Take screenshot
	{ ControlMask|ShiftMask,        XK_s,      spawn,          SHCMD("mate-screenshot -d 5") },
	// File Browser
        { MODKEY,                       XK_a,      spawn,          {.v = filecmd } },
	//Lockscreen
	{ MODKEY,        XK_l,      spawn,          SHCMD("mate-screensaver-command -l") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

