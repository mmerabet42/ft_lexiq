if exists('b:current_syntax')
	finish
endif

let b:current_syntax = 'lq'

syntax match ImportString '".*"'
syntax match ImportKeyword '#import' nextgroup=ImportString skipwhite

syntax match RuleCall '[^\]=><?}]*' contained
syntax match RuleCallAt '@' nextgroup=RuleCall contained
syntax match Metacharacter '?!\|*!\|?\|*' contained
syntax match BackSlash '\\.' contained
syntax region RuleDefinition start='"' end='"' contains=RuleCallAt,Metacharacter,BackSlash transparent
syntax match RuleName '[-_a-zA-Z0-9]\+' nextgroup=RuleDefinition skipwhite
syntax match RuleNameTransparent '-[-_a-zA-Z0-9]\+' nextgroup=RuleDefinition skipwhite


hi RuleName ctermfg=85 cterm=bold
hi RuleNameTransparent ctermfg=yellow cterm=bold
hi RuleCallAt ctermfg=86 cterm=bold
hi RuleCall ctermfg=86 cterm=bold

hi Metacharacter ctermfg=white cterm=bold
hi BackSlash cterm=bold

hi ImportKeyword ctermfg=red cterm=bold
hi ImportString ctermfg=yellow
