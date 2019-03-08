/* vi:set ts=8 sts=4 sw=4 noet:
 *
 * VIM - Vi IMproved	by Bram Moolenaar
 *
 * Do ":help uganda"  in Vim to read copying and usage conditions.
 * Do ":help credits" in Vim to see a list of people who contributed.
 */

/*
 * This file defines the Ex commands.
 * When DO_DECLARE_EXCMD is defined, the table with ex command names and
 * options results.
 * When DO_DECLARE_EXCMD is NOT defined, the enum with all the Ex commands
 * results.
 * This clever trick was invented by Ron Aaron.
 */

/*
 * When adding an Ex command:
 * 1. Add an entry in the table below.  Keep it sorted on the shortest
 *    version of the command name that works.  If it doesn't start with a
 *    lower case letter, add it at the end.
 * 2. Run "make cmdidxs" to re-generate ex_cmdidxs.h.
 * 3. Add a "case: CMD_xxx" in the big switch in ex_docmd.c.
 * 4. Add an entry in the index for Ex commands at ":help ex-cmd-index".
 * 5. Add documentation in ../doc/xxx.txt.  Add a tag for both the short and
 *    long name of the command.
 */

#ifdef RANGE
# undef RANGE			/* SASC on Amiga defines it */
#endif

#define RANGE		0x001	/* allow a linespecs */
#define BANG		0x002	/* allow a ! after the command name */
#define EXTRA		0x004	/* allow extra args after command name */
#define XFILE		0x008	/* expand wildcards in extra part */
#define NOSPC		0x010	/* no spaces allowed in the extra part */
#define	DFLALL		0x020	/* default file range is 1,$ */
#define WHOLEFOLD	0x040	/* extend range to include whole fold also
				   when less than two numbers given */
#define NEEDARG		0x080	/* argument required */
#define TRLBAR		0x100	/* check for trailing vertical bar */
#define REGSTR		0x200	/* allow "x for register designation */
#define COUNT		0x400	/* allow count in argument, after command */
#define NOTRLCOM	0x800	/* no trailing comment allowed */
#define ZEROR	       0x1000	/* zero line number allowed */
#define USECTRLV       0x2000	/* do not remove CTRL-V from argument */
#define NOTADR	       0x4000	/* number before command is not an address */
#define EDITCMD	       0x8000	/* allow "+command" argument */
#define BUFNAME	      0x10000L	/* accepts buffer name */
#define BUFUNL	      0x20000L	/* accepts unlisted buffer too */
#define ARGOPT	      0x40000L	/* allow "++opt=val" argument */
#define SBOXOK	      0x80000L	/* allowed in the sandbox */
#define CMDWIN	     0x100000L	/* allowed in cmdline window; when missing
				 * disallows editing another buffer when
				 * curbuf_lock is set */
#define MODIFY       0x200000L	/* forbidden in non-'modifiable' buffer */
#define EXFLAGS      0x400000L	/* allow flags after count in argument */
#define RESTRICT     0x800000L	/* forbidden in restricted mode */
#define FILES	(XFILE | EXTRA)	/* multiple extra files allowed */
#define WORD1	(EXTRA | NOSPC)	/* one extra word allowed */
#define FILE1	(FILES | NOSPC)	/* 1 file allowed, defaults to current file */

/* values for cmd_addr_type */
#define ADDR_LINES		0   // buffer line numbers
#define ADDR_WINDOWS		1   // window number
#define ADDR_ARGUMENTS		2   // argument number
#define ADDR_LOADED_BUFFERS	3   // buffer number of loaded buffer
#define ADDR_BUFFERS		4   // buffer number
#define ADDR_TABS		5   // tab page number
#define ADDR_TABS_RELATIVE	6   // Tab page that only relative
#define ADDR_QUICKFIX		7   // quickfix list entry number
#define ADDR_OTHER		99  // something else

#ifndef DO_DECLARE_EXCMD
typedef struct exarg exarg_T;
#endif

/*
 * This array maps ex command names to command codes.
 * The order in which command names are listed below is significant --
 * ambiguous abbreviations are always resolved to be the first possible match
 * (e.g. "r" is taken to mean "read", not "rewind", because "read" comes
 * before "rewind").
 * Not supported commands are included to avoid ambiguities.
 */
#ifdef EX
# undef EX	    /* just in case */
#endif
#ifdef DO_DECLARE_EXCMD
# define EX(a, b, c, d, e)  {(char_u *)b, c, (long_u)(d), e}

typedef void (*ex_func_T) (exarg_T *eap);

static struct cmdname
{
    char_u	*cmd_name;	/* name of the command */
    ex_func_T   cmd_func;	/* function for this command */
    long_u	cmd_argt;	/* flags declared above */
    int		cmd_addr_type;	/* flag for address type */
} cmdnames[] =
#else
# define EX(a, b, c, d, e)  a
enum CMD_index
#endif
{
EX(CMD_append,		"append",	ex_append,
			BANG|RANGE|ZEROR|TRLBAR|CMDWIN|MODIFY,
			ADDR_LINES),
EX(CMD_abbreviate,	"abbreviate",	ex_abbreviate,
			EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN,
			ADDR_LINES),
EX(CMD_abclear,		"abclear",	ex_abclear,
			EXTRA|TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_aboveleft,	"aboveleft",	ex_wrongmodifier,
			NEEDARG|EXTRA|NOTRLCOM|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_all,		"all",		ex_all,
			BANG|RANGE|NOTADR|COUNT|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_amenu,		"amenu",	ex_menu,
			RANGE|NOTADR|ZEROR|EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_anoremenu,	"anoremenu",	ex_menu,
			RANGE|NOTADR|ZEROR|EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_args,		"args",		ex_args,
			BANG|FILES|EDITCMD|ARGOPT|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_argadd,		"argadd",	ex_argadd,
			BANG|RANGE|NOTADR|ZEROR|FILES|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_ARGUMENTS),
EX(CMD_argdelete,	"argdelete",	ex_argdelete,
			BANG|RANGE|NOTADR|FILES|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_ARGUMENTS),
EX(CMD_argdo,		"argdo",	ex_listdo,
			BANG|NEEDARG|EXTRA|NOTRLCOM|RANGE|NOTADR|DFLALL|RESTRICT, /* GP added RESTRICT */
			ADDR_ARGUMENTS),
EX(CMD_argedit,		"argedit",	ex_argedit,
			BANG|NEEDARG|RANGE|NOTADR|ZEROR|FILES|EDITCMD|ARGOPT|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_ARGUMENTS),
EX(CMD_argglobal,	"argglobal",	ex_args,
			BANG|FILES|EDITCMD|ARGOPT|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_arglocal,	"arglocal",	ex_args,
			BANG|FILES|EDITCMD|ARGOPT|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_argument,	"argument",	ex_argument,
			BANG|RANGE|NOTADR|COUNT|EXTRA|EDITCMD|ARGOPT|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_ARGUMENTS),
EX(CMD_ascii,		"ascii",	do_ascii,
			TRLBAR|SBOXOK|CMDWIN,
			ADDR_LINES),
EX(CMD_autocmd,		"autocmd",	ex_autocmd,
			BANG|EXTRA|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_augroup,		"augroup",	ex_autocmd,
			BANG|WORD1|TRLBAR|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_aunmenu,		"aunmenu",	ex_menu,
			EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_buffer,		"buffer",	ex_buffer,
			BANG|RANGE|NOTADR|BUFNAME|BUFUNL|COUNT|EXTRA|EDITCMD|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_BUFFERS),
EX(CMD_bNext,		"bNext",	ex_bprevious,
			BANG|RANGE|NOTADR|COUNT|EDITCMD|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_ball,		"ball",		ex_buffer_all,
			RANGE|NOTADR|COUNT|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_badd,		"badd",		ex_edit,
			NEEDARG|FILE1|EDITCMD|TRLBAR|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_bdelete,		"bdelete",	ex_bunload,
			BANG|RANGE|NOTADR|BUFNAME|COUNT|EXTRA|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_BUFFERS),
EX(CMD_behave,		"behave",	ex_behave,
			BANG|NEEDARG|WORD1|TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_belowright,	"belowright",	ex_wrongmodifier,
			NEEDARG|EXTRA|NOTRLCOM|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_bfirst,		"bfirst",	ex_brewind,
			BANG|RANGE|NOTADR|EDITCMD|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_blast,		"blast",	ex_blast,
			BANG|RANGE|NOTADR|EDITCMD|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_bmodified,	"bmodified",	ex_bmodified,
			BANG|RANGE|NOTADR|COUNT|EDITCMD|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_bnext,		"bnext",	ex_bnext,
			BANG|RANGE|NOTADR|COUNT|EDITCMD|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_botright,	"botright",	ex_wrongmodifier,
			NEEDARG|EXTRA|NOTRLCOM|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_bprevious,	"bprevious",	ex_bprevious,
			BANG|RANGE|NOTADR|COUNT|EDITCMD|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_brewind,		"brewind",	ex_brewind,
			BANG|RANGE|NOTADR|EDITCMD|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_break,		"break",	ex_break,
			TRLBAR|SBOXOK|CMDWIN,
			ADDR_LINES),
EX(CMD_breakadd,	"breakadd",	ex_breakadd,
			EXTRA|TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_breakdel,	"breakdel",	ex_breakdel,
			EXTRA|TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_breaklist,	"breaklist",	ex_breaklist,
			EXTRA|TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_browse,		"browse",	ex_wrongmodifier,
			NEEDARG|EXTRA|NOTRLCOM|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_buffers,		"buffers",	buflist_list,
			BANG|EXTRA|TRLBAR|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_bufdo,		"bufdo",	ex_listdo,
			BANG|NEEDARG|EXTRA|NOTRLCOM|RANGE|NOTADR|DFLALL|RESTRICT, /* GP added RESTRICT */
			ADDR_BUFFERS),
EX(CMD_bunload,		"bunload",	ex_bunload,
			BANG|RANGE|NOTADR|BUFNAME|COUNT|EXTRA|TRLBAR,
			ADDR_LOADED_BUFFERS),
EX(CMD_bwipeout,	"bwipeout",	ex_bunload,
			BANG|RANGE|NOTADR|BUFNAME|BUFUNL|COUNT|EXTRA|TRLBAR,
			ADDR_BUFFERS),
EX(CMD_change,		"change",	ex_change,
			BANG|WHOLEFOLD|RANGE|COUNT|TRLBAR|CMDWIN|MODIFY,
			ADDR_LINES),
EX(CMD_cNext,		"cNext",	ex_cnext,
			RANGE|NOTADR|COUNT|TRLBAR|BANG|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_cNfile,		"cNfile",	ex_cnext,
			RANGE|NOTADR|COUNT|TRLBAR|BANG|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_cabbrev,		"cabbrev",	ex_abbreviate,
			EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN,
			ADDR_LINES),
EX(CMD_cabclear,	"cabclear",	ex_abclear,
			EXTRA|TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_caddbuffer,	"caddbuffer",	ex_cbuffer,
			RANGE|NOTADR|WORD1|TRLBAR,
			ADDR_LINES),
EX(CMD_caddexpr,	"caddexpr",	ex_cexpr,
			NEEDARG|WORD1|NOTRLCOM|TRLBAR,
			ADDR_LINES),
EX(CMD_caddfile,	"caddfile",	ex_cfile,
			TRLBAR|FILE1,
			ADDR_LINES),
EX(CMD_call,		"call",		ex_call,
			RANGE|NEEDARG|EXTRA|NOTRLCOM|SBOXOK|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_catch,		"catch",	ex_catch,
			EXTRA|SBOXOK|CMDWIN,
			ADDR_LINES),
EX(CMD_cbuffer,		"cbuffer",	ex_cbuffer,
			BANG|RANGE|NOTADR|WORD1|TRLBAR,
			ADDR_LINES),
EX(CMD_cbottom,		"cbottom",	ex_cbottom,
			TRLBAR,
			ADDR_LINES),
EX(CMD_cc,		"cc",		ex_cc,
			RANGE|NOTADR|COUNT|TRLBAR|BANG,
			ADDR_LINES),
EX(CMD_cclose,		"cclose",	ex_cclose,
			RANGE|NOTADR|COUNT|TRLBAR,
			ADDR_LINES),
EX(CMD_cd,		"cd",		ex_cd,
			BANG|FILE1|TRLBAR|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_cdo,		"cdo",		ex_listdo,
			BANG|NEEDARG|EXTRA|NOTRLCOM|RANGE|NOTADR|DFLALL|RESTRICT, /* GP added RESTRICT */
			ADDR_QUICKFIX),
EX(CMD_center,		"center",	ex_align,
			TRLBAR|RANGE|WHOLEFOLD|EXTRA|CMDWIN|MODIFY,
			ADDR_LINES),
EX(CMD_cexpr,		"cexpr",	ex_cexpr,
			NEEDARG|WORD1|NOTRLCOM|TRLBAR|BANG,
			ADDR_LINES),
EX(CMD_cfile,		"cfile",	ex_cfile,
			TRLBAR|FILE1|BANG,
			ADDR_LINES),
EX(CMD_cfdo,		"cfdo",		ex_listdo,
			BANG|NEEDARG|EXTRA|NOTRLCOM|RANGE|NOTADR|DFLALL|RESTRICT, /* GP added RESTRICT */
			ADDR_QUICKFIX),
EX(CMD_cfirst,		"cfirst",	ex_cc,
			RANGE|NOTADR|COUNT|TRLBAR|BANG,
			ADDR_LINES),
EX(CMD_cgetfile,	"cgetfile",	ex_cfile,
			TRLBAR|FILE1,
			ADDR_LINES),
EX(CMD_cgetbuffer,	"cgetbuffer",	ex_cbuffer,
			RANGE|NOTADR|WORD1|TRLBAR,
			ADDR_LINES),
EX(CMD_cgetexpr,	"cgetexpr",	ex_cexpr,
			NEEDARG|WORD1|NOTRLCOM|TRLBAR,
			ADDR_LINES),
EX(CMD_chdir,		"chdir",	ex_cd,
			BANG|FILE1|TRLBAR|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_changes,		"changes",	ex_changes,
			TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_checkpath,	"checkpath",	ex_checkpath,
			TRLBAR|BANG|CMDWIN,
			ADDR_LINES),
EX(CMD_checktime,	"checktime",	ex_checktime,
			RANGE|NOTADR|BUFNAME|COUNT|EXTRA|TRLBAR,
			ADDR_LINES),
EX(CMD_chistory,	"chistory",	qf_history,
			TRLBAR,
			ADDR_LINES),
EX(CMD_clist,		"clist",	qf_list,
			BANG|EXTRA|TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_clast,		"clast",	ex_cc,
			RANGE|NOTADR|COUNT|TRLBAR|BANG,
			ADDR_LINES),
EX(CMD_close,		"close",	ex_close,
			BANG|RANGE|NOTADR|COUNT|TRLBAR|CMDWIN,
			ADDR_WINDOWS),
EX(CMD_clearjumps,	"clearjumps",	ex_clearjumps,
			TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_cmap,		"cmap",		ex_map,
			EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_cmapclear,	"cmapclear",	ex_mapclear,
			EXTRA|TRLBAR|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_cmenu,		"cmenu",	ex_menu,
			RANGE|NOTADR|ZEROR|EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_cnext,		"cnext",	ex_cnext,
			RANGE|NOTADR|COUNT|TRLBAR|BANG|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_cnewer,		"cnewer",	qf_age,
			RANGE|NOTADR|COUNT|TRLBAR,
			ADDR_LINES),
EX(CMD_cnfile,		"cnfile",	ex_cnext,
			RANGE|NOTADR|COUNT|TRLBAR|BANG|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_cnoremap,	"cnoremap",	ex_map,
			EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_cnoreabbrev,	"cnoreabbrev",	ex_abbreviate,
			EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN,
			ADDR_LINES),
EX(CMD_cnoremenu,	"cnoremenu",	ex_menu,
			RANGE|NOTADR|ZEROR|EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_copy,		"copy",		ex_copymove,
			RANGE|WHOLEFOLD|EXTRA|TRLBAR|CMDWIN|MODIFY,
			ADDR_LINES),
EX(CMD_colder,		"colder",	qf_age,
			RANGE|NOTADR|COUNT|TRLBAR,
			ADDR_LINES),
EX(CMD_colorscheme,	"colorscheme",	ex_colorscheme,
			WORD1|TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_command,		"command",	ex_command,
			EXTRA|BANG|NOTRLCOM|USECTRLV|CMDWIN,
			ADDR_LINES),
EX(CMD_comclear,	"comclear",	ex_comclear,
			TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_compiler,	"compiler",	ex_compiler,
			BANG|TRLBAR|WORD1|CMDWIN,
			ADDR_LINES),
EX(CMD_continue,	"continue",	ex_continue,
			TRLBAR|SBOXOK|CMDWIN,
			ADDR_LINES),
EX(CMD_confirm,		"confirm",	ex_wrongmodifier,
			NEEDARG|EXTRA|NOTRLCOM|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_copen,		"copen",	ex_copen,
			RANGE|NOTADR|COUNT|TRLBAR,
			ADDR_LINES),
EX(CMD_cprevious,	"cprevious",	ex_cnext,
			RANGE|NOTADR|COUNT|TRLBAR|BANG|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_cpfile,		"cpfile",	ex_cnext,
			RANGE|NOTADR|COUNT|TRLBAR|BANG|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_cquit,		"cquit",	ex_cquit,
			TRLBAR|BANG,
			ADDR_LINES),
EX(CMD_crewind,		"crewind",	ex_cc,
			RANGE|NOTADR|COUNT|TRLBAR|BANG,
			ADDR_LINES),
EX(CMD_cscope,		"cscope",	ex_cscope,
			EXTRA|NOTRLCOM|XFILE,
			ADDR_LINES),
EX(CMD_cstag,		"cstag",	ex_cstag,
			BANG|TRLBAR|WORD1,
			ADDR_LINES),
EX(CMD_cunmap,		"cunmap",	ex_unmap,
			EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_cunabbrev,	"cunabbrev",	ex_abbreviate,
			EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN,
			ADDR_LINES),
EX(CMD_cunmenu,		"cunmenu",	ex_menu,
			EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_cwindow,		"cwindow",	ex_cwindow,
			RANGE|NOTADR|COUNT|TRLBAR,
			ADDR_LINES),
EX(CMD_delete,		"delete",	ex_operators,
			RANGE|WHOLEFOLD|REGSTR|COUNT|TRLBAR|CMDWIN|MODIFY,
			ADDR_LINES),
EX(CMD_delmarks,	"delmarks",	ex_delmarks,
			BANG|EXTRA|TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_debug,		"debug",	ex_debug,
			NEEDARG|EXTRA|NOTRLCOM|SBOXOK|CMDWIN,
			ADDR_LINES),
EX(CMD_debuggreedy,	"debuggreedy",	ex_debuggreedy,
			RANGE|NOTADR|ZEROR|TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_delcommand,	"delcommand",	ex_delcommand,
			NEEDARG|WORD1|TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_delfunction,	"delfunction",	ex_delfunction,
			BANG|NEEDARG|WORD1|CMDWIN,
			ADDR_LINES),
EX(CMD_display,		"display",	ex_display,
			EXTRA|NOTRLCOM|TRLBAR|SBOXOK|CMDWIN,
			ADDR_LINES),
EX(CMD_diffupdate,	"diffupdate",	ex_diffupdate,
			BANG|TRLBAR,
			ADDR_LINES),
EX(CMD_diffget,		"diffget",	ex_diffgetput,
			RANGE|EXTRA|TRLBAR|MODIFY,
			ADDR_LINES),
EX(CMD_diffoff,		"diffoff",	ex_diffoff,
			BANG|TRLBAR,
			ADDR_LINES),
EX(CMD_diffpatch,	"diffpatch",	ex_diffpatch,
			EXTRA|FILE1|TRLBAR|MODIFY,
			ADDR_LINES),
EX(CMD_diffput,		"diffput",	ex_diffgetput,
			RANGE|EXTRA|TRLBAR,
			ADDR_LINES),
EX(CMD_diffsplit,	"diffsplit",	ex_diffsplit,
			EXTRA|FILE1|TRLBAR,
			ADDR_LINES),
EX(CMD_diffthis,	"diffthis",	ex_diffthis,
			TRLBAR,
			ADDR_LINES),
EX(CMD_digraphs,	"digraphs",	ex_digraphs,
			BANG|EXTRA|TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_djump,		"djump",	ex_findpat,
			BANG|RANGE|DFLALL|WHOLEFOLD|EXTRA,
			ADDR_LINES),
EX(CMD_dlist,		"dlist",	ex_findpat,
			BANG|RANGE|DFLALL|WHOLEFOLD|EXTRA|CMDWIN,
			ADDR_LINES),
EX(CMD_doautocmd,	"doautocmd",	ex_doautocmd,
			EXTRA|TRLBAR|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_doautoall,	"doautoall",	ex_doautoall,
			EXTRA|TRLBAR|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_drop,		"drop",		ex_drop,
			FILES|EDITCMD|NEEDARG|ARGOPT|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_dsearch,		"dsearch",	ex_findpat,
			BANG|RANGE|DFLALL|WHOLEFOLD|EXTRA|CMDWIN,
			ADDR_LINES),
EX(CMD_dsplit,		"dsplit",	ex_findpat,
			BANG|RANGE|DFLALL|WHOLEFOLD|EXTRA,
			ADDR_LINES),
EX(CMD_edit,		"edit",		ex_edit,
			BANG|FILE1|EDITCMD|ARGOPT|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_earlier,		"earlier",	ex_later,
			TRLBAR|EXTRA|NOSPC|CMDWIN,
			ADDR_LINES),
EX(CMD_echo,		"echo",		ex_echo,
			EXTRA|NOTRLCOM|SBOXOK|CMDWIN,
			ADDR_LINES),
EX(CMD_echoerr,		"echoerr",	ex_execute,
			EXTRA|NOTRLCOM|SBOXOK|CMDWIN,
			ADDR_LINES),
EX(CMD_echohl,		"echohl",	ex_echohl,
			EXTRA|TRLBAR|SBOXOK|CMDWIN,
			ADDR_LINES),
EX(CMD_echomsg,		"echomsg",	ex_execute,
			EXTRA|NOTRLCOM|SBOXOK|CMDWIN,
			ADDR_LINES),
EX(CMD_echon,		"echon",	ex_echo,
			EXTRA|NOTRLCOM|SBOXOK|CMDWIN,
			ADDR_LINES),
EX(CMD_else,		"else",		ex_else,
			TRLBAR|SBOXOK|CMDWIN,
			ADDR_LINES),
EX(CMD_elseif,		"elseif",	ex_else,
			EXTRA|NOTRLCOM|SBOXOK|CMDWIN,
			ADDR_LINES),
EX(CMD_emenu,		"emenu",	ex_emenu,
			NEEDARG|EXTRA|TRLBAR|NOTRLCOM|RANGE|NOTADR|CMDWIN,
			ADDR_LINES),
EX(CMD_endif,		"endif",	ex_endif,
			TRLBAR|SBOXOK|CMDWIN,
			ADDR_LINES),
EX(CMD_endfunction,	"endfunction",	ex_endfunction,
			TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_endfor,		"endfor",	ex_endwhile,
			TRLBAR|SBOXOK|CMDWIN,
			ADDR_LINES),
EX(CMD_endtry,		"endtry",	ex_endtry,
			TRLBAR|SBOXOK|CMDWIN,
			ADDR_LINES),
EX(CMD_endwhile,	"endwhile",	ex_endwhile,
			TRLBAR|SBOXOK|CMDWIN,
			ADDR_LINES),
EX(CMD_enew,		"enew",		ex_edit,
			BANG|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_ex,		"ex",		ex_edit,
			BANG|FILE1|EDITCMD|ARGOPT|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_execute,		"execute",	ex_execute,
			EXTRA|NOTRLCOM|SBOXOK|CMDWIN,
			ADDR_LINES),
EX(CMD_exit,		"exit",		ex_exit,
			/* RANGE|WHOLEFOLD|BANG|FILE1|ARGOPT|DFLALL|TRLBAR|CMDWIN,  * GP */
			RANGE|WHOLEFOLD|BANG|DFLALL|TRLBAR, /* GP */
			ADDR_LINES),
EX(CMD_exusage,		"exusage",	ex_exusage,
			TRLBAR,
			ADDR_LINES),
EX(CMD_file,		"file",		ex_file,
			RANGE|NOTADR|ZEROR|BANG|FILE1|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_files,		"files",	buflist_list,
			BANG|EXTRA|TRLBAR|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_filetype,	"filetype",	ex_filetype,
			EXTRA|TRLBAR|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_filter,		"filter",	ex_wrongmodifier,
			BANG|NEEDARG|EXTRA|NOTRLCOM|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_find,		"find",		ex_find,
			RANGE|NOTADR|BANG|FILE1|EDITCMD|ARGOPT|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_finally,		"finally",	ex_finally,
			TRLBAR|SBOXOK|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_finish,		"finish",	ex_finish,
			TRLBAR|SBOXOK|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_first,		"first",	ex_rewind,
			EXTRA|BANG|EDITCMD|ARGOPT|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_fixdel,		"fixdel",	do_fixdel,
			TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_fold,		"fold",		ex_fold,
			RANGE|WHOLEFOLD|TRLBAR|SBOXOK|CMDWIN,
			ADDR_LINES),
EX(CMD_foldclose,	"foldclose",	ex_foldopen,
			RANGE|BANG|WHOLEFOLD|TRLBAR|SBOXOK|CMDWIN,
			ADDR_LINES),
EX(CMD_folddoopen,	"folddoopen",	ex_folddo,
			RANGE|DFLALL|NEEDARG|EXTRA|NOTRLCOM,
			ADDR_LINES),
EX(CMD_folddoclosed,	"folddoclosed",	ex_folddo,
			RANGE|DFLALL|NEEDARG|EXTRA|NOTRLCOM,
			ADDR_LINES),
EX(CMD_foldopen,	"foldopen",	ex_foldopen,
			RANGE|BANG|WHOLEFOLD|TRLBAR|SBOXOK|CMDWIN,
			ADDR_LINES),
EX(CMD_for,		"for",		ex_while,
			EXTRA|NOTRLCOM|SBOXOK|CMDWIN,
			ADDR_LINES),
EX(CMD_function,	"function",	ex_function,
			EXTRA|BANG|SBOXOK|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_global,		"global",	ex_global,
			RANGE|WHOLEFOLD|BANG|EXTRA|DFLALL|SBOXOK|CMDWIN,
			ADDR_LINES),
EX(CMD_goto,		"goto",		ex_goto,
			RANGE|NOTADR|COUNT|TRLBAR|SBOXOK|CMDWIN,
			ADDR_LINES),
EX(CMD_grep,		"grep",		ex_make,
			RANGE|NOTADR|BANG|NEEDARG|EXTRA|NOTRLCOM|TRLBAR|XFILE,
			ADDR_LINES),
EX(CMD_grepadd,		"grepadd",	ex_make,
			RANGE|NOTADR|BANG|NEEDARG|EXTRA|NOTRLCOM|TRLBAR|XFILE,
			ADDR_LINES),
EX(CMD_gui,		"gui",		ex_gui,
			BANG|FILES|EDITCMD|ARGOPT|TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_gvim,		"gvim",		ex_gui,
			BANG|FILES|EDITCMD|ARGOPT|TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_help,		"help",		ex_help,
			BANG|EXTRA|NOTRLCOM,
			ADDR_LINES),
EX(CMD_helpclose,	"helpclose",	ex_helpclose,
			RANGE|NOTADR|COUNT|TRLBAR,
			ADDR_LINES),
EX(CMD_helpfind,	"helpfind",	ex_helpfind,
			EXTRA|NOTRLCOM,
			ADDR_LINES),
EX(CMD_helpgrep,	"helpgrep",	ex_helpgrep,
			EXTRA|NOTRLCOM|NEEDARG,
			ADDR_LINES),
EX(CMD_helptags,	"helptags",	ex_helptags,
			NEEDARG|FILES|TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_hardcopy,	"hardcopy",	ex_hardcopy,
			RANGE|COUNT|EXTRA|TRLBAR|DFLALL|BANG,
			ADDR_LINES),
EX(CMD_highlight,	"highlight",	ex_highlight,
			BANG|EXTRA|TRLBAR|SBOXOK|CMDWIN,
			ADDR_LINES),
EX(CMD_hide,		"hide",		ex_hide,
			BANG|RANGE|NOTADR|COUNT|EXTRA|TRLBAR,
			ADDR_WINDOWS),
EX(CMD_history,		"history",	ex_history,
			EXTRA|TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_insert,		"insert",	ex_append,
			BANG|RANGE|TRLBAR|CMDWIN|MODIFY,
			ADDR_LINES),
EX(CMD_iabbrev,		"iabbrev",	ex_abbreviate,
			EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN,
			ADDR_LINES),
EX(CMD_iabclear,	"iabclear",	ex_abclear,
			EXTRA|TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_if,		"if",		ex_if,
			EXTRA|NOTRLCOM|SBOXOK|CMDWIN,
			ADDR_LINES),
EX(CMD_ijump,		"ijump",	ex_findpat,
			BANG|RANGE|DFLALL|WHOLEFOLD|EXTRA,
			ADDR_LINES),
EX(CMD_ilist,		"ilist",	ex_findpat,
			BANG|RANGE|DFLALL|WHOLEFOLD|EXTRA|CMDWIN,
			ADDR_LINES),
EX(CMD_imap,		"imap",		ex_map,
			EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_imapclear,	"imapclear",	ex_mapclear,
			EXTRA|TRLBAR|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_imenu,		"imenu",	ex_menu,
			RANGE|NOTADR|ZEROR|EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_inoremap,	"inoremap",	ex_map,
			EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_inoreabbrev,	"inoreabbrev",	ex_abbreviate,
			EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN,
			ADDR_LINES),
EX(CMD_inoremenu,	"inoremenu",	ex_menu,
			RANGE|NOTADR|ZEROR|EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_intro,		"intro",	ex_intro,
			TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_isearch,		"isearch",	ex_findpat,
			BANG|RANGE|DFLALL|WHOLEFOLD|EXTRA|CMDWIN,
			ADDR_LINES),
EX(CMD_isplit,		"isplit",	ex_findpat,
			BANG|RANGE|DFLALL|WHOLEFOLD|EXTRA,
			ADDR_LINES),
EX(CMD_iunmap,		"iunmap",	ex_unmap,
			EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_iunabbrev,	"iunabbrev",	ex_abbreviate,
			EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN,
			ADDR_LINES),
EX(CMD_iunmenu,		"iunmenu",	ex_menu,
			EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_join,		"join",		ex_join,
			BANG|RANGE|WHOLEFOLD|COUNT|EXFLAGS|TRLBAR|CMDWIN|MODIFY,
			ADDR_LINES),
EX(CMD_jumps,		"jumps",	ex_jumps,
			TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_k,		"k",		ex_mark,
			RANGE|WORD1|TRLBAR|SBOXOK|CMDWIN,
			ADDR_LINES),
EX(CMD_keepmarks,	"keepmarks",	ex_wrongmodifier,
			NEEDARG|EXTRA|NOTRLCOM|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_keepjumps,	"keepjumps",	ex_wrongmodifier,
			NEEDARG|EXTRA|NOTRLCOM|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_keeppatterns,	"keeppatterns",	ex_wrongmodifier,
			NEEDARG|EXTRA|NOTRLCOM|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_keepalt,		"keepalt",	ex_wrongmodifier,
			NEEDARG|EXTRA|NOTRLCOM|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_list,		"list",		ex_print,
			RANGE|WHOLEFOLD|COUNT|EXFLAGS|TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_lNext,		"lNext",	ex_cnext,
			RANGE|NOTADR|COUNT|TRLBAR|BANG|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_lNfile,		"lNfile",	ex_cnext,
			RANGE|NOTADR|COUNT|TRLBAR|BANG|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_last,		"last",		ex_last,
			EXTRA|BANG|EDITCMD|ARGOPT|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_language,	"language",	ex_language,
			EXTRA|TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_laddexpr,	"laddexpr",	ex_cexpr,
			NEEDARG|WORD1|NOTRLCOM|TRLBAR,
			ADDR_LINES),
EX(CMD_laddbuffer,	"laddbuffer",	ex_cbuffer,
			RANGE|NOTADR|WORD1|TRLBAR,
			ADDR_LINES),
EX(CMD_laddfile,	"laddfile",	ex_cfile,
			TRLBAR|FILE1,
			ADDR_LINES),
EX(CMD_later,		"later",	ex_later,
			TRLBAR|EXTRA|NOSPC|CMDWIN,
			ADDR_LINES),
EX(CMD_lbuffer,		"lbuffer",	ex_cbuffer,
			BANG|RANGE|NOTADR|WORD1|TRLBAR,
			ADDR_LINES),
EX(CMD_lbottom,		"lbottom",	ex_cbottom,
			TRLBAR,
			ADDR_LINES),
EX(CMD_lcd,		"lcd",		ex_cd,
			BANG|FILE1|TRLBAR|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_lchdir,		"lchdir",	ex_cd,
			BANG|FILE1|TRLBAR|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_lclose,		"lclose",	ex_cclose,
			RANGE|NOTADR|COUNT|TRLBAR,
			ADDR_LINES),
EX(CMD_lcscope,		"lcscope",	ex_cscope,
			EXTRA|NOTRLCOM|XFILE,
			ADDR_LINES),
EX(CMD_ldo,		"ldo",		ex_listdo,
			BANG|NEEDARG|EXTRA|NOTRLCOM|RANGE|NOTADR|DFLALL|RESTRICT, /* GP added RESTRICT */
			ADDR_QUICKFIX),
EX(CMD_left,		"left",		ex_align,
			TRLBAR|RANGE|WHOLEFOLD|EXTRA|CMDWIN|MODIFY,
			ADDR_LINES),
EX(CMD_leftabove,	"leftabove",	ex_wrongmodifier,
			NEEDARG|EXTRA|NOTRLCOM|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_let,		"let",		ex_let,
			EXTRA|NOTRLCOM|SBOXOK|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_lexpr,		"lexpr",	ex_cexpr,
			NEEDARG|WORD1|NOTRLCOM|TRLBAR|BANG,
			ADDR_LINES),
EX(CMD_lfile,		"lfile",	ex_cfile,
			TRLBAR|FILE1|BANG,
			ADDR_LINES),
EX(CMD_lfdo,		"lfdo",		ex_listdo,
			BANG|NEEDARG|EXTRA|NOTRLCOM|RANGE|NOTADR|DFLALL|RESTRICT, /* GP added RESTRICT */
			ADDR_QUICKFIX),
EX(CMD_lfirst,		"lfirst",	ex_cc,
			RANGE|NOTADR|COUNT|TRLBAR|BANG,
			ADDR_LINES),
EX(CMD_lgetfile,	"lgetfile",	ex_cfile,
			TRLBAR|FILE1,
			ADDR_LINES),
EX(CMD_lgetbuffer,	"lgetbuffer",	ex_cbuffer,
			RANGE|NOTADR|WORD1|TRLBAR,
			ADDR_LINES),
EX(CMD_lgetexpr,	"lgetexpr",	ex_cexpr,
			NEEDARG|WORD1|NOTRLCOM|TRLBAR,
			ADDR_LINES),
EX(CMD_lgrep,		"lgrep",	ex_make,
			RANGE|NOTADR|BANG|NEEDARG|EXTRA|NOTRLCOM|TRLBAR|XFILE,
			ADDR_LINES),
EX(CMD_lgrepadd,	"lgrepadd",	ex_make,
			RANGE|NOTADR|BANG|NEEDARG|EXTRA|NOTRLCOM|TRLBAR|XFILE,
			ADDR_LINES),
EX(CMD_lhelpgrep,	"lhelpgrep",	ex_helpgrep,
			EXTRA|NOTRLCOM|NEEDARG,
			ADDR_LINES),
EX(CMD_lhistory,	"lhistory",	qf_history,
			TRLBAR,
			ADDR_LINES),
EX(CMD_ll,		"ll",		ex_cc,
			RANGE|NOTADR|COUNT|TRLBAR|BANG,
			ADDR_LINES),
EX(CMD_llast,		"llast",	ex_cc,
			RANGE|NOTADR|COUNT|TRLBAR|BANG,
			ADDR_LINES),
EX(CMD_llist,		"llist",	qf_list,
			BANG|EXTRA|TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_lmap,		"lmap",		ex_map,
			EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_lmapclear,	"lmapclear",	ex_mapclear,
			EXTRA|TRLBAR|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_lmake,		"lmake",	ex_make,
			BANG|EXTRA|NOTRLCOM|TRLBAR|XFILE,
			ADDR_LINES),
EX(CMD_lnoremap,	"lnoremap",	ex_map,
			EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_lnext,		"lnext",	ex_cnext,
			RANGE|NOTADR|COUNT|TRLBAR|BANG|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_lnewer,		"lnewer",	qf_age,
			RANGE|NOTADR|COUNT|TRLBAR,
			ADDR_LINES),
EX(CMD_lnfile,		"lnfile",	ex_cnext,
			RANGE|NOTADR|COUNT|TRLBAR|BANG|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_loadview,	"loadview",	ex_loadview,
			FILE1|TRLBAR,
			ADDR_LINES),
EX(CMD_loadkeymap,	"loadkeymap",	ex_loadkeymap,
			CMDWIN,
			ADDR_LINES),
EX(CMD_lockmarks,	"lockmarks",	ex_wrongmodifier,
			NEEDARG|EXTRA|NOTRLCOM|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_lockvar,		"lockvar",	ex_lockvar,
			BANG|EXTRA|NEEDARG|SBOXOK|CMDWIN,
			ADDR_LINES),
EX(CMD_lolder,		"lolder",	qf_age,
			RANGE|NOTADR|COUNT|TRLBAR,
			ADDR_LINES),
EX(CMD_lopen,		"lopen",	ex_copen,
			RANGE|NOTADR|COUNT|TRLBAR,
			ADDR_LINES),
EX(CMD_lprevious,	"lprevious",	ex_cnext,
			RANGE|NOTADR|COUNT|TRLBAR|BANG|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_lpfile,		"lpfile",	ex_cnext,
			RANGE|NOTADR|COUNT|TRLBAR|BANG|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_lrewind,		"lrewind",	ex_cc,
			RANGE|NOTADR|COUNT|TRLBAR|BANG,
			ADDR_LINES),
EX(CMD_ltag,		"ltag",		ex_tag,
			NOTADR|TRLBAR|BANG|WORD1|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_lunmap,		"lunmap",	ex_unmap,
			EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_lua,		"lua",		ex_lua,
			RANGE|EXTRA|NEEDARG|CMDWIN|RESTRICT,
			ADDR_LINES),
EX(CMD_luado,		"luado",	ex_luado,
			RANGE|DFLALL|EXTRA|NEEDARG|CMDWIN|RESTRICT,
			ADDR_LINES),
EX(CMD_luafile,		"luafile",	ex_luafile,
			RANGE|FILE1|NEEDARG|CMDWIN|RESTRICT,
			ADDR_LINES),
EX(CMD_lvimgrep,	"lvimgrep",	ex_vimgrep,
			RANGE|NOTADR|BANG|NEEDARG|EXTRA|NOTRLCOM|TRLBAR|XFILE,
			ADDR_LINES),
EX(CMD_lvimgrepadd,	"lvimgrepadd",	ex_vimgrep,
			RANGE|NOTADR|BANG|NEEDARG|EXTRA|NOTRLCOM|TRLBAR|XFILE,
			ADDR_LINES),
EX(CMD_lwindow,		"lwindow",	ex_cwindow,
			RANGE|NOTADR|COUNT|TRLBAR,
			ADDR_LINES),
EX(CMD_ls,		"ls",		buflist_list,
			BANG|EXTRA|TRLBAR|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_move,		"move",		ex_copymove,
			RANGE|WHOLEFOLD|EXTRA|TRLBAR|CMDWIN|MODIFY,
			ADDR_LINES),
EX(CMD_mark,		"mark",		ex_mark,
			RANGE|WORD1|TRLBAR|SBOXOK|CMDWIN,
			ADDR_LINES),
EX(CMD_make,		"make",		ex_make,
			BANG|EXTRA|NOTRLCOM|TRLBAR|XFILE,
			ADDR_LINES),
EX(CMD_map,		"map",		ex_map,
			BANG|EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_mapclear,	"mapclear",	ex_mapclear,
			EXTRA|BANG|TRLBAR|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_marks,		"marks",	do_marks,
			EXTRA|TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_match,		"match",	ex_match,
			RANGE|NOTADR|EXTRA|CMDWIN,
			ADDR_LINES),
EX(CMD_menu,		"menu",		ex_menu,
			RANGE|NOTADR|ZEROR|BANG|EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_menutranslate,	"menutranslate", ex_menutranslate,
			EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN,
			ADDR_LINES),
EX(CMD_messages,	"messages",	ex_messages,
			EXTRA|TRLBAR|RANGE|CMDWIN,
			ADDR_OTHER),
EX(CMD_mkexrc,		"mkexrc",	ex_mkrc,
			BANG|FILE1|TRLBAR|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_mksession,	"mksession",	ex_mkrc,
			BANG|FILE1|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_mkspell,		"mkspell",	ex_mkspell,
			BANG|NEEDARG|EXTRA|NOTRLCOM|TRLBAR|XFILE|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_mkvimrc,		"mkvimrc",	ex_mkrc,
			BANG|FILE1|TRLBAR|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_mkview,		"mkview",	ex_mkrc,
			BANG|FILE1|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_mode,		"mode",		ex_mode,
			WORD1|TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_mzscheme,	"mzscheme",	ex_mzscheme,
			RANGE|EXTRA|DFLALL|NEEDARG|CMDWIN|SBOXOK|RESTRICT,
			ADDR_LINES),
EX(CMD_mzfile,		"mzfile",	ex_mzfile,
			RANGE|FILE1|NEEDARG|CMDWIN|RESTRICT,
			ADDR_LINES),
EX(CMD_next,		"next",		ex_next,
			RANGE|NOTADR|BANG|FILES|EDITCMD|ARGOPT|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_nbkey,		"nbkey",	ex_nbkey,
			EXTRA|NOTADR|NEEDARG,
			ADDR_LINES),
EX(CMD_nbclose,		"nbclose",	ex_nbclose,
			TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_nbstart,		"nbstart",	ex_nbstart,
			WORD1|TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_new,		"new",		ex_splitview,
			BANG|FILE1|RANGE|NOTADR|EDITCMD|ARGOPT|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_nmap,		"nmap",		ex_map,
			EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_nmapclear,	"nmapclear",	ex_mapclear,
			EXTRA|TRLBAR|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_nmenu,		"nmenu",	ex_menu,
			RANGE|NOTADR|ZEROR|EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_nnoremap,	"nnoremap",	ex_map,
			EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_nnoremenu,	"nnoremenu",	ex_menu,
			RANGE|NOTADR|ZEROR|EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_noremap,		"noremap",	ex_map,
			BANG|EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_noautocmd,	"noautocmd",	ex_wrongmodifier,
			NEEDARG|EXTRA|NOTRLCOM|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_nohlsearch,	"nohlsearch",	ex_nohlsearch,
			TRLBAR|SBOXOK|CMDWIN,
			ADDR_LINES),
EX(CMD_noreabbrev,	"noreabbrev",	ex_abbreviate,
			EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN,
			ADDR_LINES),
EX(CMD_noremenu,	"noremenu",	ex_menu,
			RANGE|NOTADR|ZEROR|BANG|EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_noswapfile,	"noswapfile",	ex_wrongmodifier,
			NEEDARG|EXTRA|NOTRLCOM|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_normal,		"normal",	ex_normal,
			RANGE|BANG|EXTRA|NEEDARG|NOTRLCOM|USECTRLV|SBOXOK|CMDWIN,
			ADDR_LINES),
EX(CMD_number,		"number",	ex_print,
			RANGE|WHOLEFOLD|COUNT|EXFLAGS|TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_nunmap,		"nunmap",	ex_unmap,
			EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_nunmenu,		"nunmenu",	ex_menu,
			EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_open,		"open",		ex_open,
			RANGE|BANG|EXTRA|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_oldfiles,	"oldfiles",	ex_oldfiles,
			BANG|TRLBAR|SBOXOK|CMDWIN,
			ADDR_LINES),
EX(CMD_omap,		"omap",		ex_map,
			EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_omapclear,	"omapclear",	ex_mapclear,
			EXTRA|TRLBAR|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_omenu,		"omenu",	ex_menu,
			RANGE|NOTADR|ZEROR|EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_only,		"only",		ex_only,
			BANG|NOTADR|RANGE|COUNT|TRLBAR,
			ADDR_WINDOWS),
EX(CMD_onoremap,	"onoremap",	ex_map,
			EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_onoremenu,	"onoremenu",	ex_menu,
			RANGE|NOTADR|ZEROR|EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_options,		"options",	ex_options,
			TRLBAR,
			ADDR_LINES),
EX(CMD_ounmap,		"ounmap",	ex_unmap,
			EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_ounmenu,		"ounmenu",	ex_menu,
			EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_ownsyntax,	"ownsyntax",	ex_ownsyntax,
			EXTRA|NOTRLCOM|SBOXOK|CMDWIN,
			ADDR_LINES),
EX(CMD_print,		"print",	ex_print,
			RANGE|WHOLEFOLD|COUNT|EXFLAGS|TRLBAR|CMDWIN|SBOXOK|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_packadd,		"packadd",	ex_packadd,
			BANG|FILE1|NEEDARG|TRLBAR|SBOXOK|CMDWIN,
			ADDR_LINES),
EX(CMD_packloadall,	"packloadall",	ex_packloadall,
			BANG|TRLBAR|SBOXOK|CMDWIN,
			ADDR_LINES),
EX(CMD_pclose,		"pclose",	ex_pclose,
			BANG|TRLBAR,
			ADDR_LINES),
EX(CMD_perl,		"perl",		ex_perl,
			RANGE|EXTRA|DFLALL|NEEDARG|SBOXOK|CMDWIN,
			ADDR_LINES),
EX(CMD_perldo,		"perldo",	ex_perldo,
			RANGE|EXTRA|DFLALL|NEEDARG|CMDWIN,
			ADDR_LINES),
EX(CMD_pedit,		"pedit",	ex_pedit,
			BANG|FILE1|EDITCMD|ARGOPT|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_pop,		"pop",		ex_tag,
			RANGE|NOTADR|BANG|COUNT|TRLBAR|ZEROR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_popup,		"popup",	ex_popup,
			NEEDARG|EXTRA|BANG|TRLBAR|NOTRLCOM|CMDWIN,
			ADDR_LINES),
EX(CMD_ppop,		"ppop",		ex_ptag,
			RANGE|NOTADR|BANG|COUNT|TRLBAR|ZEROR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_preserve,	"preserve",	ex_preserve,
			TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_previous,	"previous",	ex_previous,
			EXTRA|RANGE|NOTADR|COUNT|BANG|EDITCMD|ARGOPT|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_promptfind,	"promptfind",	gui_mch_find_dialog,
			EXTRA|NOTRLCOM|CMDWIN,
			ADDR_LINES),
EX(CMD_promptrepl,	"promptrepl",	gui_mch_replace_dialog,
			EXTRA|NOTRLCOM|CMDWIN,
			ADDR_LINES),
EX(CMD_profile,		"profile",	ex_profile,
			BANG|EXTRA|TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_profdel,		"profdel",	ex_breakdel,
			EXTRA|TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_psearch,		"psearch",	ex_psearch,
			BANG|RANGE|WHOLEFOLD|DFLALL|EXTRA,
			ADDR_LINES),
EX(CMD_ptag,		"ptag",		ex_ptag,
			RANGE|NOTADR|BANG|WORD1|TRLBAR|ZEROR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_ptNext,		"ptNext",	ex_ptag,
			RANGE|NOTADR|BANG|TRLBAR|ZEROR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_ptfirst,		"ptfirst",	ex_ptag,
			RANGE|NOTADR|BANG|TRLBAR|ZEROR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_ptjump,		"ptjump",	ex_ptag,
			BANG|TRLBAR|WORD1|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_ptlast,		"ptlast",	ex_ptag,
			BANG|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_ptnext,		"ptnext",	ex_ptag,
			RANGE|NOTADR|BANG|TRLBAR|ZEROR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_ptprevious,	"ptprevious",	ex_ptag,
			RANGE|NOTADR|BANG|TRLBAR|ZEROR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_ptrewind,	"ptrewind",	ex_ptag,
			RANGE|NOTADR|BANG|TRLBAR|ZEROR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_ptselect,	"ptselect",	ex_ptag,
			BANG|TRLBAR|WORD1|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_put,		"put",		ex_put,
			RANGE|WHOLEFOLD|BANG|REGSTR|TRLBAR|ZEROR|CMDWIN|MODIFY,
			ADDR_LINES),
EX(CMD_pwd,		"pwd",		ex_pwd,
			TRLBAR|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_python,		"python",	ex_python,
			RANGE|EXTRA|NEEDARG|CMDWIN|RESTRICT,
			ADDR_LINES),
EX(CMD_pydo,		"pydo",		ex_pydo,
			RANGE|DFLALL|EXTRA|NEEDARG|CMDWIN|RESTRICT,
			ADDR_LINES),
EX(CMD_pyfile,		"pyfile",	ex_pyfile,
			RANGE|FILE1|NEEDARG|CMDWIN|RESTRICT,
			ADDR_LINES),
EX(CMD_py3,		"py3",		ex_py3,
			RANGE|EXTRA|NEEDARG|CMDWIN|RESTRICT,
			ADDR_LINES),
EX(CMD_py3do,		"py3do",	ex_py3do,
			RANGE|DFLALL|EXTRA|NEEDARG|CMDWIN|RESTRICT,
			ADDR_LINES),
EX(CMD_python3,		"python3",	ex_py3,
			RANGE|EXTRA|NEEDARG|CMDWIN|RESTRICT,
			ADDR_LINES),
EX(CMD_py3file,		"py3file",	ex_py3file,
			RANGE|FILE1|NEEDARG|CMDWIN|RESTRICT,
			ADDR_LINES),
EX(CMD_pyx,		"pyx",		ex_pyx,
			RANGE|EXTRA|NEEDARG|CMDWIN|RESTRICT,
			ADDR_LINES),
EX(CMD_pyxdo,		"pyxdo",	ex_pyxdo,
			RANGE|DFLALL|EXTRA|NEEDARG|CMDWIN|RESTRICT,
			ADDR_LINES),
EX(CMD_pythonx,		"pythonx",	ex_pyx,
			RANGE|EXTRA|NEEDARG|CMDWIN|RESTRICT,
			ADDR_LINES),
EX(CMD_pyxfile,		"pyxfile",	ex_pyxfile,
			RANGE|FILE1|NEEDARG|CMDWIN|RESTRICT,
			ADDR_LINES),
EX(CMD_quit,		"quit",		ex_quit,
			BANG|RANGE|COUNT|NOTADR|TRLBAR|CMDWIN,
			ADDR_WINDOWS),
EX(CMD_quitall,		"quitall",	ex_quit_all,
			BANG|TRLBAR,
			ADDR_LINES),
EX(CMD_qall,		"qall",		ex_quit_all,
			BANG|TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_read,		"read",		ex_read,
			BANG|RANGE|WHOLEFOLD|FILE1|ARGOPT|TRLBAR|ZEROR|CMDWIN|MODIFY|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_recover,		"recover",	ex_recover,
			BANG|FILE1|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_redo,		"redo",		ex_redo,
			TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_redir,		"redir",	ex_redir,
			BANG|FILES|TRLBAR|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_redraw,		"redraw",	ex_redraw,
			BANG|TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_redrawstatus,	"redrawstatus",	ex_redrawstatus,
			BANG|TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_redrawtabline,	"redrawtabline", ex_redrawtabline,
			TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_registers,	"registers",	ex_display,
			EXTRA|NOTRLCOM|TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_resize,		"resize",	ex_resize,
			RANGE|NOTADR|TRLBAR|WORD1|CMDWIN,
			ADDR_LINES),
EX(CMD_retab,		"retab",	ex_retab,
			TRLBAR|RANGE|WHOLEFOLD|DFLALL|BANG|WORD1|CMDWIN|MODIFY,
			ADDR_LINES),
EX(CMD_return,		"return",	ex_return,
			EXTRA|NOTRLCOM|SBOXOK|CMDWIN,
			ADDR_LINES),
EX(CMD_rewind,		"rewind",	ex_rewind,
			EXTRA|BANG|EDITCMD|ARGOPT|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_right,		"right",	ex_align,
			TRLBAR|RANGE|WHOLEFOLD|EXTRA|CMDWIN|MODIFY,
			ADDR_LINES),
EX(CMD_rightbelow,	"rightbelow",	ex_wrongmodifier,
			NEEDARG|EXTRA|NOTRLCOM|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_runtime,		"runtime",	ex_runtime,
			BANG|NEEDARG|FILES|TRLBAR|SBOXOK|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_ruby,		"ruby",		ex_ruby,
			RANGE|EXTRA|NEEDARG|CMDWIN|RESTRICT,
			ADDR_LINES),
EX(CMD_rubydo,		"rubydo",	ex_rubydo,
			RANGE|DFLALL|EXTRA|NEEDARG|CMDWIN|RESTRICT,
			ADDR_LINES),
EX(CMD_rubyfile,	"rubyfile",	ex_rubyfile,
			RANGE|FILE1|NEEDARG|CMDWIN|RESTRICT,
			ADDR_LINES),
EX(CMD_rundo,		"rundo",	ex_rundo,
			NEEDARG|FILE1,
			ADDR_LINES),
EX(CMD_rviminfo,	"rviminfo",	ex_viminfo,
			BANG|FILE1|TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_substitute,	"substitute",	do_sub,
			RANGE|WHOLEFOLD|EXTRA|CMDWIN,
			ADDR_LINES),
EX(CMD_sNext,		"sNext",	ex_previous,
			EXTRA|RANGE|NOTADR|COUNT|BANG|EDITCMD|ARGOPT|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_sargument,	"sargument",	ex_argument,
			BANG|RANGE|NOTADR|COUNT|EXTRA|EDITCMD|ARGOPT|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_ARGUMENTS),
EX(CMD_sall,		"sall",		ex_all,
			BANG|RANGE|NOTADR|COUNT|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_sandbox,		"sandbox",	ex_wrongmodifier,
			NEEDARG|EXTRA|NOTRLCOM|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_saveas,		"saveas",	ex_write,
			BANG|DFLALL|FILE1|ARGOPT|CMDWIN|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_sbuffer,		"sbuffer",	ex_buffer,
			BANG|RANGE|NOTADR|BUFNAME|BUFUNL|COUNT|EXTRA|EDITCMD|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_BUFFERS),
EX(CMD_sbNext,		"sbNext",	ex_bprevious,
			RANGE|NOTADR|COUNT|EDITCMD|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_sball,		"sball",	ex_buffer_all,
			RANGE|NOTADR|COUNT|EDITCMD|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_sbfirst,		"sbfirst",	ex_brewind,
			EDITCMD|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_sblast,		"sblast",	ex_blast,
			EDITCMD|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_sbmodified,	"sbmodified",	ex_bmodified,
			RANGE|NOTADR|COUNT|EDITCMD|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_sbnext,		"sbnext",	ex_bnext,
			RANGE|NOTADR|COUNT|EDITCMD|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_sbprevious,	"sbprevious",	ex_bprevious,
			RANGE|NOTADR|COUNT|EDITCMD|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_sbrewind,	"sbrewind",	ex_brewind,
			EDITCMD|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_scriptnames,	"scriptnames",	ex_scriptnames,
			BANG|RANGE|NOTADR|COUNT|TRLBAR|CMDWIN,
			ADDR_OTHER),
EX(CMD_scriptencoding,	"scriptencoding", ex_scriptencoding,
			WORD1|TRLBAR|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_scscope,		"scscope",	ex_scscope,
			EXTRA|NOTRLCOM,
			ADDR_LINES),
EX(CMD_set,		"set",		ex_set,
			TRLBAR|EXTRA|CMDWIN|SBOXOK,
			ADDR_LINES),
EX(CMD_setfiletype,	"setfiletype",	ex_setfiletype,
			TRLBAR|EXTRA|NEEDARG|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_setglobal,	"setglobal",	ex_set,
			TRLBAR|EXTRA|CMDWIN|SBOXOK|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_setlocal,	"setlocal",	ex_set,
			TRLBAR|EXTRA|CMDWIN|SBOXOK|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_sfind,		"sfind",	ex_splitview,
			BANG|FILE1|RANGE|NOTADR|EDITCMD|ARGOPT|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_sfirst,		"sfirst",	ex_rewind,
			EXTRA|BANG|EDITCMD|ARGOPT|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_shell,		"shell",	ex_shell,
			TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_simalt,		"simalt",	ex_simalt,
			NEEDARG|WORD1|TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_sign,		"sign",		ex_sign,
			NEEDARG|RANGE|NOTADR|EXTRA|CMDWIN,
			ADDR_LINES),
EX(CMD_silent,		"silent",	ex_wrongmodifier,
			NEEDARG|EXTRA|BANG|NOTRLCOM|SBOXOK|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_sleep,		"sleep",	ex_sleep,
			RANGE|NOTADR|COUNT|EXTRA|TRLBAR|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_slast,		"slast",	ex_last,
			EXTRA|BANG|EDITCMD|ARGOPT|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_smagic,		"smagic",	ex_submagic,
			RANGE|WHOLEFOLD|EXTRA|CMDWIN,
			ADDR_LINES),
EX(CMD_smap,		"smap",		ex_map,
			EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_smapclear,	"smapclear",	ex_mapclear,
			EXTRA|TRLBAR|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_smenu,		"smenu",	ex_menu,
			RANGE|NOTADR|ZEROR|EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_snext,		"snext",	ex_next,
			RANGE|NOTADR|BANG|FILES|EDITCMD|ARGOPT|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_snomagic,	"snomagic",	ex_submagic,
			RANGE|WHOLEFOLD|EXTRA|CMDWIN,
			ADDR_LINES),
EX(CMD_snoremap,	"snoremap",	ex_map,
			EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_snoremenu,	"snoremenu",	ex_menu,
			RANGE|NOTADR|ZEROR|EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_source,		"source",	ex_source,
			BANG|FILE1|TRLBAR|SBOXOK|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES), 
EX(CMD_sort,		"sort",		ex_sort,
			RANGE|DFLALL|WHOLEFOLD|BANG|EXTRA|NOTRLCOM|MODIFY,
			ADDR_LINES),
EX(CMD_split,		"split",	ex_splitview,
			BANG|FILE1|RANGE|NOTADR|EDITCMD|ARGOPT|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_spellgood,	"spellgood",	ex_spell,
			BANG|RANGE|NOTADR|NEEDARG|EXTRA|TRLBAR,
			ADDR_LINES),
EX(CMD_spelldump,	"spelldump",	ex_spelldump,
			BANG|TRLBAR,
			ADDR_LINES),
EX(CMD_spellinfo,	"spellinfo",	ex_spellinfo,
			TRLBAR,
			ADDR_LINES),
EX(CMD_spellrepall,	"spellrepall",	ex_spellrepall,
			TRLBAR,
			ADDR_LINES),
EX(CMD_spellundo,	"spellundo",	ex_spell,
			BANG|RANGE|NOTADR|NEEDARG|EXTRA|TRLBAR,
			ADDR_LINES),
EX(CMD_spellwrong,	"spellwrong",	ex_spell,
			BANG|RANGE|NOTADR|NEEDARG|EXTRA|TRLBAR,
			ADDR_LINES),
EX(CMD_sprevious,	"sprevious",	ex_previous,
			EXTRA|RANGE|NOTADR|COUNT|BANG|EDITCMD|ARGOPT|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_srewind,		"srewind",	ex_rewind,
			EXTRA|BANG|EDITCMD|ARGOPT|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_stop,		"stop",		ex_stop,
			TRLBAR|BANG|CMDWIN,
			ADDR_LINES),
EX(CMD_stag,		"stag",		ex_stag,
			RANGE|NOTADR|BANG|WORD1|TRLBAR|ZEROR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_startinsert,	"startinsert",	ex_startinsert,
			BANG|TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_startgreplace,	"startgreplace", ex_startinsert,
			BANG|TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_startreplace,	"startreplace",	ex_startinsert,
			BANG|TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_stopinsert,	"stopinsert",	ex_stopinsert,
			BANG|TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_stjump,		"stjump",	ex_stag,
			BANG|TRLBAR|WORD1|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_stselect,	"stselect",	ex_stag,
			BANG|TRLBAR|WORD1|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_sunhide,		"sunhide",	ex_buffer_all,
			RANGE|NOTADR|COUNT|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_sunmap,		"sunmap",	ex_unmap,
			EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_sunmenu,		"sunmenu",	ex_menu,
			EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_suspend,		"suspend",	ex_stop,
			TRLBAR|BANG|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_sview,		"sview",	ex_splitview,
			BANG|FILE1|RANGE|NOTADR|EDITCMD|ARGOPT|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_swapname,	"swapname",	ex_swapname,
			TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_syntax,		"syntax",	ex_syntax,
			EXTRA|NOTRLCOM|CMDWIN,
			ADDR_LINES),
EX(CMD_syntime,		"syntime",	ex_syntime,
			NEEDARG|WORD1|TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_syncbind,	"syncbind",	ex_syncbind,
			TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_smile,		"smile",	ex_smile,
			TRLBAR|CMDWIN|SBOXOK,
			ADDR_LINES),
EX(CMD_t,		"t",		ex_copymove,
			RANGE|WHOLEFOLD|EXTRA|TRLBAR|CMDWIN|MODIFY,
			ADDR_LINES),
EX(CMD_tNext,		"tNext",	ex_tag,
			RANGE|NOTADR|BANG|TRLBAR|ZEROR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_tag,		"tag",		ex_tag,
			RANGE|NOTADR|BANG|WORD1|TRLBAR|ZEROR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_tags,		"tags",		do_tags,
			TRLBAR|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_tab,		"tab",		ex_wrongmodifier,
			NEEDARG|EXTRA|NOTRLCOM|RESTRICT, /* GP added RESTRICT */
			ADDR_TABS),
EX(CMD_tabclose,	"tabclose",	ex_tabclose,
			BANG|RANGE|NOTADR|ZEROR|EXTRA|NOSPC|TRLBAR|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_TABS),
EX(CMD_tabdo,		"tabdo",	ex_listdo,
			NEEDARG|EXTRA|NOTRLCOM|RANGE|NOTADR|DFLALL|RESTRICT, /* GP added RESTRICT */
			ADDR_TABS),
EX(CMD_tabedit,		"tabedit",	ex_splitview,
			BANG|FILE1|RANGE|NOTADR|ZEROR|EDITCMD|ARGOPT|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_TABS),
EX(CMD_tabfind,		"tabfind",	ex_splitview,
			BANG|FILE1|RANGE|NOTADR|ZEROR|EDITCMD|ARGOPT|NEEDARG|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_TABS),
EX(CMD_tabfirst,	"tabfirst",	ex_tabnext,
			TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_TABS),
EX(CMD_tabmove,		"tabmove",	ex_tabmove,
			RANGE|NOTADR|ZEROR|EXTRA|NOSPC|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_TABS),
EX(CMD_tablast,		"tablast",	ex_tabnext,
			TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_TABS),
EX(CMD_tabnext,		"tabnext",	ex_tabnext,
			RANGE|NOTADR|ZEROR|EXTRA|NOSPC|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_TABS),
EX(CMD_tabnew,		"tabnew",	ex_splitview,
			BANG|FILE1|RANGE|NOTADR|ZEROR|EDITCMD|ARGOPT|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_TABS),
EX(CMD_tabonly,		"tabonly",	ex_tabonly,
			BANG|RANGE|NOTADR|ZEROR|EXTRA|NOSPC|TRLBAR|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_TABS),
EX(CMD_tabprevious,	"tabprevious",	ex_tabnext,
			RANGE|NOTADR|ZEROR|EXTRA|NOSPC|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_TABS_RELATIVE),
EX(CMD_tabNext,		"tabNext",	ex_tabnext,
			RANGE|NOTADR|ZEROR|EXTRA|NOSPC|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_TABS_RELATIVE),
EX(CMD_tabrewind,	"tabrewind",	ex_tabnext,
			TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_TABS),
EX(CMD_tabs,		"tabs",		ex_tabs,
			TRLBAR|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_TABS),
EX(CMD_tcl,		"tcl",		ex_tcl,
			RANGE|EXTRA|NEEDARG|CMDWIN|RESTRICT,
			ADDR_LINES),
EX(CMD_tcldo,		"tcldo",	ex_tcldo,
			RANGE|DFLALL|EXTRA|NEEDARG|CMDWIN|RESTRICT,
			ADDR_LINES),
EX(CMD_tclfile,		"tclfile",	ex_tclfile,
			RANGE|FILE1|NEEDARG|CMDWIN|RESTRICT,
			ADDR_LINES),
EX(CMD_tearoff,		"tearoff",	ex_tearoff,
			NEEDARG|EXTRA|TRLBAR|NOTRLCOM|CMDWIN,
			ADDR_LINES),
EX(CMD_terminal,	"terminal",	ex_terminal,
			RANGE|BANG|FILES|CMDWIN,
			ADDR_LINES),
EX(CMD_tfirst,		"tfirst",	ex_tag,
			RANGE|NOTADR|BANG|TRLBAR|ZEROR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_throw,		"throw",	ex_throw,
			EXTRA|NEEDARG|SBOXOK|CMDWIN,
			ADDR_LINES),
EX(CMD_tjump,		"tjump",	ex_tag,
			BANG|TRLBAR|WORD1|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_tlast,		"tlast",	ex_tag,
			BANG|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_tlmenu,		"tlmenu",	ex_menu,
			RANGE|NOTADR|ZEROR|EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_tlnoremenu,	"tlnoremenu",	ex_menu,
			RANGE|NOTADR|ZEROR|EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_tlunmenu,	"tlunmenu",	ex_menu,
			RANGE|NOTADR|ZEROR|EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_tmenu,		"tmenu",	ex_menu,
			RANGE|NOTADR|ZEROR|EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_tmap,		"tmap",		ex_map,
			EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_tmapclear,	"tmapclear",	ex_mapclear,
			EXTRA|TRLBAR|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_tnext,		"tnext",	ex_tag,
			RANGE|NOTADR|BANG|TRLBAR|ZEROR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_tnoremap,	"tnoremap",	ex_map,
			EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_topleft,		"topleft",	ex_wrongmodifier,
			NEEDARG|EXTRA|NOTRLCOM|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_tprevious,	"tprevious",	ex_tag,
			RANGE|NOTADR|BANG|TRLBAR|ZEROR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_trewind,		"trewind",	ex_tag,
			RANGE|NOTADR|BANG|TRLBAR|ZEROR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_try,		"try",		ex_try,
			TRLBAR|SBOXOK|CMDWIN,
			ADDR_LINES),
EX(CMD_tselect,		"tselect",	ex_tag,
			BANG|TRLBAR|WORD1|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_tunmenu,		"tunmenu",	ex_menu,
			EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_tunmap,		"tunmap",	ex_unmap,
			EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_undo,		"undo",		ex_undo,
			RANGE|NOTADR|COUNT|ZEROR|TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_undojoin,	"undojoin",	ex_undojoin,
			TRLBAR|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_undolist,	"undolist",	ex_undolist,
			TRLBAR|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_unabbreviate,	"unabbreviate",	ex_abbreviate,
			EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN,
			ADDR_LINES),
EX(CMD_unhide,		"unhide",	ex_buffer_all,
			RANGE|NOTADR|COUNT|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_unlet,		"unlet",	ex_unlet,
			BANG|EXTRA|NEEDARG|SBOXOK|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_unlockvar,	"unlockvar",	ex_lockvar,
			BANG|EXTRA|NEEDARG|SBOXOK|CMDWIN,
			ADDR_LINES),
EX(CMD_unmap,		"unmap",	ex_unmap,
			BANG|EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_unmenu,		"unmenu",	ex_menu,
			BANG|EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_unsilent,	"unsilent",	ex_wrongmodifier,
			NEEDARG|EXTRA|NOTRLCOM|SBOXOK|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_update,		"update",	ex_update,
			RANGE|WHOLEFOLD|BANG|FILE1|ARGOPT|DFLALL|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_vglobal,		"vglobal",	ex_global,
			RANGE|WHOLEFOLD|EXTRA|DFLALL|CMDWIN,
			ADDR_LINES),
EX(CMD_version,		"version",	ex_version,
			EXTRA|TRLBAR|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_verbose,		"verbose",	ex_wrongmodifier,
			NEEDARG|RANGE|NOTADR|EXTRA|NOTRLCOM|SBOXOK|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_vertical,	"vertical",	ex_wrongmodifier,
			NEEDARG|EXTRA|NOTRLCOM|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_visual,		"visual",	ex_edit,
			BANG|FILE1|EDITCMD|ARGOPT|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_view,		"view",		ex_edit,
			BANG|FILE1|EDITCMD|ARGOPT|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_vimgrep,		"vimgrep",	ex_vimgrep,
			RANGE|NOTADR|BANG|NEEDARG|EXTRA|NOTRLCOM|TRLBAR|XFILE,
			ADDR_LINES),
EX(CMD_vimgrepadd,	"vimgrepadd",	ex_vimgrep,
			RANGE|NOTADR|BANG|NEEDARG|EXTRA|NOTRLCOM|TRLBAR|XFILE,
			ADDR_LINES),
EX(CMD_viusage,		"viusage",	ex_viusage,
			TRLBAR,
			ADDR_LINES),
EX(CMD_vmap,		"vmap",		ex_map,
			EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_vmapclear,	"vmapclear",	ex_mapclear,
			EXTRA|TRLBAR|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_vmenu,		"vmenu",	ex_menu,
			RANGE|NOTADR|ZEROR|EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_vnoremap,	"vnoremap",	ex_map,
			EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_vnew,		"vnew",		ex_splitview,
			BANG|FILE1|RANGE|NOTADR|EDITCMD|ARGOPT|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_vnoremenu,	"vnoremenu",	ex_menu,
			RANGE|NOTADR|ZEROR|EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_vsplit,		"vsplit",	ex_splitview,
			BANG|FILE1|RANGE|NOTADR|EDITCMD|ARGOPT|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_vunmap,		"vunmap",	ex_unmap,
			EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_vunmenu,		"vunmenu",	ex_menu,
			EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_write,		"write",	ex_write,
			RANGE|WHOLEFOLD|BANG|FILE1|ARGOPT|DFLALL|TRLBAR|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_wNext,		"wNext",	ex_wnext,
			RANGE|WHOLEFOLD|NOTADR|BANG|FILE1|ARGOPT|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_wall,		"wall",		do_wqall,
			BANG|TRLBAR|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_while,		"while",	ex_while,
			EXTRA|NOTRLCOM|SBOXOK|CMDWIN,
			ADDR_LINES),
EX(CMD_winsize,		"winsize",	ex_winsize,
			EXTRA|NEEDARG|TRLBAR,
			ADDR_LINES),
EX(CMD_wincmd,		"wincmd",	ex_wincmd,
			NEEDARG|WORD1|RANGE|NOTADR|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_WINDOWS),
EX(CMD_windo,		"windo",	ex_listdo,
			NEEDARG|EXTRA|NOTRLCOM|RANGE|NOTADR|DFLALL|RESTRICT, /* GP added RESTRICT */
			ADDR_WINDOWS),
EX(CMD_winpos,		"winpos",	ex_winpos,
			EXTRA|TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_wnext,		"wnext",	ex_wnext,
			RANGE|NOTADR|BANG|FILE1|ARGOPT|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_wprevious,	"wprevious",	ex_wnext,
			RANGE|NOTADR|BANG|FILE1|ARGOPT|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_wq,		"wq",		ex_exit,
			/* RANGE|WHOLEFOLD|BANG|FILE1|ARGOPT|DFLALL|TRLBAR, * GP */
			RANGE|WHOLEFOLD|BANG|DFLALL|TRLBAR, /* GP */
			ADDR_LINES),
EX(CMD_wqall,		"wqall",	do_wqall,
			BANG|FILE1|ARGOPT|DFLALL|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_wundo,		"wundo",	ex_wundo,
			BANG|NEEDARG|FILE1,
			ADDR_LINES),
EX(CMD_wviminfo,	"wviminfo",	ex_viminfo,
			BANG|FILE1|TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_xit,		"xit",		ex_exit,
			/* RANGE|WHOLEFOLD|BANG|FILE1|ARGOPT|DFLALL|TRLBAR|CMDWIN, * GP */
			RANGE|WHOLEFOLD|BANG|DFLALL|TRLBAR, /* GP */
			ADDR_LINES),
EX(CMD_xall,		"xall",		do_wqall,
			BANG|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_xmap,		"xmap",		ex_map,
			EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_xmapclear,	"xmapclear",	ex_mapclear,
			EXTRA|TRLBAR|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_xmenu,		"xmenu",	ex_menu,
			RANGE|NOTADR|ZEROR|EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_xnoremap,	"xnoremap",	ex_map,
			EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_xnoremenu,	"xnoremenu",	ex_menu,
			RANGE|NOTADR|ZEROR|EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_xunmap,		"xunmap",	ex_unmap,
			EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_xunmenu,		"xunmenu",	ex_menu,
			EXTRA|TRLBAR|NOTRLCOM|USECTRLV|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_yank,		"yank",		ex_operators,
			RANGE|WHOLEFOLD|REGSTR|COUNT|TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_z,		"z",		ex_z,
			RANGE|WHOLEFOLD|EXTRA|EXFLAGS|TRLBAR|CMDWIN,
			ADDR_LINES),

/* commands that don't start with a lowercase letter */
EX(CMD_bang,		"!",		ex_bang,
			RANGE|WHOLEFOLD|BANG|FILES|CMDWIN,
			ADDR_LINES),
EX(CMD_pound,		"#",		ex_print,
			RANGE|WHOLEFOLD|COUNT|EXFLAGS|TRLBAR|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_and,		"&",		do_sub,
			RANGE|WHOLEFOLD|EXTRA|CMDWIN|MODIFY,
			ADDR_LINES),
EX(CMD_star,		"*",		ex_at,
			RANGE|WHOLEFOLD|EXTRA|TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_lshift,		"<",		ex_operators,
			RANGE|WHOLEFOLD|COUNT|EXFLAGS|TRLBAR|CMDWIN|MODIFY,
			ADDR_LINES),
EX(CMD_equal,		"=",		ex_equal,
			RANGE|TRLBAR|DFLALL|EXFLAGS|CMDWIN,
			ADDR_LINES),
EX(CMD_rshift,		">",		ex_operators,
			RANGE|WHOLEFOLD|COUNT|EXFLAGS|TRLBAR|CMDWIN|MODIFY,
			ADDR_LINES),
EX(CMD_at,		"@",		ex_at,
			RANGE|WHOLEFOLD|EXTRA|TRLBAR|CMDWIN,
			ADDR_LINES),
EX(CMD_Next,		"Next",		ex_previous,
			EXTRA|RANGE|NOTADR|COUNT|BANG|EDITCMD|ARGOPT|TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_Print,		"Print",	ex_print,
			RANGE|WHOLEFOLD|COUNT|EXFLAGS|TRLBAR|CMDWIN|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_X,		"X",		ex_X,
			TRLBAR|RESTRICT, /* GP added RESTRICT */
			ADDR_LINES),
EX(CMD_tilde,		"~",		do_sub,
			RANGE|WHOLEFOLD|EXTRA|CMDWIN|MODIFY,
			ADDR_LINES),

#ifndef DO_DECLARE_EXCMD
#ifdef FEAT_USR_CMDS
    CMD_SIZE,		/* MUST be after all real commands! */
    CMD_USER = -1,	/* User-defined command */
    CMD_USER_BUF = -2	/* User-defined command local to buffer */
#else
    CMD_SIZE	/* MUST be the last one! */
#endif
#endif
};

#ifndef DO_DECLARE_EXCMD
typedef enum CMD_index cmdidx_T;

/*
 * Arguments used for Ex commands.
 */
struct exarg
{
    char_u	*arg;		/* argument of the command */
    char_u	*nextcmd;	/* next command (NULL if none) */
    char_u	*cmd;		/* the name of the command (except for :make) */
    char_u	**cmdlinep;	/* pointer to pointer of allocated cmdline */
    cmdidx_T	cmdidx;		/* the index for the command */
    long	argt;		/* flags for the command */
    int		skip;		/* don't execute the command, only parse it */
    int		forceit;	/* TRUE if ! present */
    int		addr_count;	/* the number of addresses given */
    linenr_T	line1;		/* the first line number */
    linenr_T	line2;		/* the second line number or count */
    int		addr_type;	/* type of the count/range */
    int		flags;		/* extra flags after count: EXFLAG_ */
    char_u	*do_ecmd_cmd;	/* +command arg to be used in edited file */
    linenr_T	do_ecmd_lnum;	/* the line number in an edited file */
    int		append;		/* TRUE with ":w >>file" command */
    int		usefilter;	/* TRUE with ":w !command" and ":r!command" */
    int		amount;		/* number of '>' or '<' for shift command */
    int		regname;	/* register name (NUL if none) */
    int		force_bin;	/* 0, FORCE_BIN or FORCE_NOBIN */
    int		read_edit;	/* ++edit argument */
    int		force_ff;	/* ++ff= argument (first char of argument) */
    int		force_enc;	/* ++enc= argument (index in cmd[]) */
    int		bad_char;	/* BAD_KEEP, BAD_DROP or replacement byte */
#ifdef FEAT_USR_CMDS
    int		useridx;	/* user command index */
#endif
    char	*errmsg;	/* returned error message */
    char_u	*(*getline)(int, void *, int);
    void	*cookie;	/* argument for getline() */
#ifdef FEAT_EVAL
    struct condstack *cstack;	/* condition stack for ":if" etc. */
#endif
    long	verbose_save;	 // saved value of p_verbose
    int		save_msg_silent; // saved value of msg_silent
    int		did_esilent;	 // how many times emsg_silent was incremented
#ifdef HAVE_SANDBOX
    int		did_sandbox;	// when TRUE did ++sandbox
#endif
};

#define FORCE_BIN 1		/* ":edit ++bin file" */
#define FORCE_NOBIN 2		/* ":edit ++nobin file" */

/* Values for "flags" */
#define EXFLAG_LIST	0x01	/* 'l': list */
#define EXFLAG_NR	0x02	/* '#': number */
#define EXFLAG_PRINT	0x04	/* 'p': print */

#endif
