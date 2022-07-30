/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 4;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 4;       /* vert inner gap between windows */
static const unsigned int gappoh    = 4;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 4;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int focusonwheel       = 0;
static const char *fonts[]          = { "JetBrainsMono Nerd Font:style=Medium:size=12", 
                                        "JoyPixels:size=12"};
static const char dmenufont[]       = "monospace:size=10";

/* following colours only for declaring purposes; values will be overwritten by Xresources */
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char tag1[]                  = "#222222";
static char tag2[]                  = "#222222";
static char tag3[]                  = "#222222";
static char tag4[]                  = "#222222";
static char tag5[]                  = "#222222";
static char tag6[]                  = "#222222";

static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

static char *tag_colors[][2] = {
       /* fg           bg  */
       { tag1,     normbgcolor},
       { tag2,     normbgcolor},
       { tag3,     normbgcolor},
       { tag4,     normbgcolor},
       { tag5,     normbgcolor},
       { tag6,     normbgcolor},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6"};
static const char *lt_stack[] = {"", "", "", "", "", "", "", "", "", "", " ", ""};
static const char *occupy[] = {"", ""};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "vanitygaps.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ " ",       deck },  /* first entry is default */
	{ " ",       monocle },
	{ " ",       bstack },
	{ " ",       NULL },    /* no layout function means floating behavior */
	{ " ",       spiral },
	{ " ",       tile },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	/* new tags will be toggled for the new, but not yet spawned client(s) */ \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	/* new tags will be toggled for the current focused client */ \
	{ MODKEY|ControlMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *volume_increase[] = {"volume.sh", "up", NULL};
static const char *volume_decrease[] = {"volume.sh", "down", NULL};
static const char *volume_mute[] = {"volume.sh", "mute", NULL};
static const char *light_increase[] = {"brightness.sh", "up", NULL};
static const char *light_decrease[] = {"brightness.sh", "down", NULL};

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "background", STRING,  &normbgcolor },
		{ "color7",     STRING,  &normbordercolor },
		{ "foreground", STRING,  &normfgcolor },
		{ "color4",     STRING,  &selbgcolor },
		{ "color1",     STRING,  &selbordercolor },
		{ "foreground", STRING,  &selfgcolor },
		{ "color9",     STRING,  &tag1 },
		{ "color10",    STRING,  &tag2 },
		{ "color11",    STRING,  &tag3 },
		{ "color12",    STRING,  &tag4 },
		{ "color13",    STRING,  &tag5 },
		{ "color14",    STRING,  &tag6 },
};

static Key keys[] = {
	/* modifier                     key        function        argument */
	{0,              XF86XK_AudioMute,         spawn,          {.v = volume_mute}},
        {0,              XF86XK_AudioRaiseVolume,  spawn,          {.v = volume_increase}},
        {0,              XF86XK_AudioLowerVolume,  spawn,          {.v = volume_decrease}},
        {0,              XF86XK_MonBrightnessUp,   spawn,          {.v = light_increase}},
	{0,              XF86XK_MonBrightnessDown, spawn,          {.v = light_decrease}},
	{ MODKEY,                       XK_t,      spawn,          SHCMD("toggle_bar.sh") },
	{ MODKEY,                       XK_w,      spawn,          SHCMD("wallpaper.sh") },
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_n,      shiftview,      {.i = +1 } },
	{ MODKEY,                       XK_b,      shiftview,      {.i = -1 } },
	{ MODKEY,                       XK_m,      msaltfocus,     {0} },
	{ MODKEY,                       XK_z,      zoom,           {0} },
	{ MODKEY,                       XK_Left,   setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_Right,  setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_f,      togglefullscreen, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_Up,     layoutscroll,   {.i = -1 } },
	{ MODKEY,                       XK_Down,   layoutscroll,   {.i = +1 } },
	{ MODKEY,                       XK_g,      togglegaps,     {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	//{ MODKEY|Mod1Mask,              XK_u,      incrgaps,       {.i = +1 } },
	//{ MODKEY|Mod1Mask|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } },
	//{ MODKEY|Mod1Mask,              XK_i,      incrigaps,      {.i = +1 } },
	//{ MODKEY|Mod1Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
	//{ MODKEY|Mod1Mask,              XK_o,      incrogaps,      {.i = +1 } },
	//{ MODKEY|Mod1Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
	//{ MODKEY|Mod1Mask,              XK_6,      incrihgaps,     {.i = +1 } },
	//{ MODKEY|Mod1Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
	//{ MODKEY|Mod1Mask,              XK_7,      incrivgaps,     {.i = +1 } },
	//{ MODKEY|Mod1Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
	//{ MODKEY|Mod1Mask,              XK_8,      incrohgaps,     {.i = +1 } },
	//{ MODKEY|Mod1Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
	//{ MODKEY|Mod1Mask,              XK_9,      incrovgaps,     {.i = +1 } },
	//{ MODKEY|Mod1Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
	//{ MODKEY|Mod1Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
