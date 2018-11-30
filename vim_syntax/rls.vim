if exists('b:current_syntax')
	finish
endif

let b:current_syntax = 'rls'

syntax match ImportString '".*"'
syntax match ImportKeyword '#import' nextgroup=ImportString skipwhite

syntax match RuleCall '[^\]=><?}]*' contained
syntax match RuleCallAt '@' nextgroup=RuleCall
syntax match Metacharacter '?!\|*!\|?\|*'
syntax match BackSlash '\\.'
syntax region RuleDefinition start='"' end='"' contains=RuleCallAt,Metacharacter,BackSlash transparent
syntax match RuleName '\w\+' nextgroup=RuleDefinition skipwhite
syntax match RuleNameTransparent '-\w\+' nextgroup=RuleDefinition skipwhite


hi RuleName ctermfg=85 cterm=bold
hi RuleNameTransparent ctermfg=yellow cterm=bold
hi RuleCallAt ctermfg=86 cterm=bold
hi RuleCall ctermfg=86 cterm=bold
hi Metacharacter ctermfg=white cterm=bold
hi BackSlash cterm=bold

hi ImportKeyword ctermfg=red cterm=bold
hi ImportString ctermfg=yellow
