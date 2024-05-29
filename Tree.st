Object subclass: #Node
    instanceVariableNames: 'data left right'
    classVariableNames: ''
    poolDictionaries: ''!

!Node class methodsFor: 'creation'!
data: anObject
    ^self new initialize: anObject
!!

!Node methodsFor: 'homework'!
initialize: anObject
    data := anObject
!

insert: anObject
    anObject <= data ifTrue: [
        left isNil ifTrue: [
            ^left := Node data: anObject
        ] ifFalse: [
            ^left insert: anObject
        ]
    ] ifFalse: [
        right isNil ifTrue: [
            ^right := Node data: anObject
        ] ifFalse: [
            ^right insert: anObject
        ]
    ]
!

member: anObject
    anObject < data ifTrue: [
		left isNil ifTrue: [
			^false
		] ifFalse: [
			^left member: anObject
		]
	] .

    anObject < data ifTrue: [
		right isNil ifTrue: [
			^false
		] ifFalse: [
			^right member: anObject
		]
	] .

	^true
!!

Object subclass: #Tree
    instanceVariableNames: 'root'
    classVariableNames: ''
    poolDictionaries: ''!

!Tree class methodsFor: 'creation'!
new
    ^super new initialize
!!

!Tree methodsFor: 'homework'!
initialize 
    root := nil
!

insert: anObject
    root isNil ifTrue: [
        ^root := Node data: anObject
    ] ifFalse: [
        ^root insert: anObject
    ] 
!

member: anObject
	root isNil ifTrue: [
        ^false
    ] ifFalse: [
        ^root member: anObject
    ].

    ^true
!!
