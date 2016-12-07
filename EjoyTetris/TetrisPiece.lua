--Piece
local I,J,L,O,T,S,Z={ },{ },{ },{ },{ },{ },{ }

function init(tbl)
	local i,j
	for i=1,4 do
		tbl[i]={ }
		for j=1,5 do
			tbl[i][j]={ }
		end
	end
end

init(I)
init(J)
init(L)
init(O)
init(T)
init(S)
init(Z)

I[1]={
	{nil,nil,nil,nil,nil},
	{nil,nil,1  ,nil,nil},
	{nil,nil,1  ,nil,nil},
	{nil,nil,1  ,nil,nil},
	{nil,nil,1  ,nil,nil},
}
I[2]={
	{nil,nil,nil,nil,nil},
	{nil,nil,nil,nil,nil},
	{nil,1  ,1  ,1  ,1  },
	{nil,nil,nil,nil,nil},
	{nil,nil,nil,nil,nil},
}
I[3]={
	{nil,nil,nil,nil,nil},
	{nil,nil,1  ,nil,nil},
	{nil,nil,1  ,nil,nil},
	{nil,nil,1  ,nil,nil},
	{nil,nil,1  ,nil,nil},
}

I[4]={
	{nil,nil,nil,nil,nil},
	{nil,nil,nil,nil,nil},
	{nil,1  ,1  ,1  ,1  },
	{nil,nil,nil,nil,nil},
	{nil,nil,nil,nil,nil},
}

--J
J[1]={
	{nil,nil,nil,nil,nil},
	{nil,nil,1  ,nil,nil},
	{nil,nil,1  ,nil,nil},
	{nil,1  ,1  ,nil,nil},
	{nil,nil,nil,nil,nil}
}
J[2]={
	{nil,nil,nil,nil,nil},
	{nil,nil,nil,nil,nil},
	{nil,1  ,1  ,1  ,nil},
	{nil,nil,nil,1  ,nil},
	{nil,nil,nil,nil,nil}
}
J[3]={
	{nil,nil,nil,nil,nil},
	{nil,nil,1  ,1  ,nil},
	{nil,nil,1  ,nil,nil},
	{nil,nil,1  ,nil,nil},
	{nil,nil,nil,nil,nil}
}
J[4]={
	{nil,nil,nil,nil,nil},
	{nil,nil,1  ,nil,nil},
	{nil,nil,1  ,1  ,1  },
	{nil,nil,nil,nil,nil},
	{nil,nil,nil,nil,nil},
}

--L
L[1]={
	{ nil,nil,nil,nil,nil },
	{ nil,nil,1  ,nil,nil },
	{ nil,nil,1  ,nil,nil },
	{ nil,nil,1  ,1  ,nil },
	{ nil,nil,nil,nil,nil }
}
L[2]={
	{ nil,nil,nil,nil,nil },
	{ nil,nil,nil,1  ,nil },
	{ nil,1  ,1  ,1  ,nil },
	{ nil,nil,nil,nil,nil },
	{ nil,nil,nil,nil,nil }
}
L[3]={
	{ nil,nil,nil,nil,nil },
	{ nil,1  ,1  ,nil,nil },
	{ nil,nil,1  ,nil,nil },
	{ nil,nil,1  ,nil,nil },
	{ nil,nil,nil,nil,nil }
}
L[4]={
	{ nil,nil,nil,nil,nil },
	{ nil,1  ,1  ,1  ,nil },
	{ nil,1  ,nil,nil,nil },
	{ nil,nil,nil,nil,nil },
	{ nil,nil,nil,nil,nil }
}

--O
O[1]={
	{ nil,nil,nil,nil,nil },
	{ nil,1  ,1  ,nil,nil },
	{ nil,1  ,1  ,nil,nil },
	{ nil,nil,nil,nil,nil },
	{ nil,nil,nil,nil,nil }
}
O[2]={
	{ nil,nil,nil,nil,nil },
	{ nil,1  ,1  ,nil,nil },
	{ nil,1  ,1  ,nil,nil },
	{ nil,nil,nil,nil,nil },
	{ nil,nil,nil,nil,nil }
}
O[3]={
	{ nil,nil,nil,nil,nil },
	{ nil,1  ,1  ,nil,nil },
	{ nil,1  ,1  ,nil,nil },
	{ nil,nil,nil,nil,nil },
	{ nil,nil,nil,nil,nil }
}
O[4]={
	{ nil,nil,nil,nil,nil },
	{ nil,1  ,1  ,nil,nil },
	{ nil,1  ,1  ,nil,nil },
	{ nil,nil,nil,nil,nil },
	{ nil,nil,nil,nil,nil }
}
--S
S[1]={
	{ nil,nil,nil,nil,nil },
	{ nil,nil,1  ,1  ,nil },
	{ nil,1  ,1  ,nil,nil },
	{ nil,nil,nil,nil,nil },
	{ nil,nil,nil,nil,nil }
}
S[2]={
	{ nil,nil,nil,nil,nil },
	{ nil,nil,1  ,nil,nil },
	{ nil,nil,1  ,1,  nil },
	{ nil,nil,nil,1  ,nil },
	{ nil,nil,nil,nil,nil }
}
S[3]={
	{ nil,nil,nil,nil,nil },
	{ nil,nil,1  ,1  ,nil },
	{ nil,1  ,1  ,nil,nil },
	{ nil,nil,nil,nil,nil },
	{ nil,nil,nil,nil,nil }
}
S[4]={
	{ nil,nil,nil,nil,nil },
	{ nil,nil,1  ,nil,nil },
	{ nil,nil,1  ,1  ,nil },
	{ nil,nil,nil,1  ,nil },
	{ nil,nil,nil,nil,nil }
}

--T
T[1]={
	{ nil,nil,nil,nil,nil },
	{ nil,nil,nil,nil,nil },
	{ nil,1  ,1  ,1  ,nil },
	{ nil,nil,1  ,nil,nil },
	{ nil,nil,nil,nil,nil }
}
T[2]={
	{ nil,nil,nil,nil,nil },
	{ nil,nil,1  ,nil,nil },
	{ nil,nil,1  ,1  ,nil },
	{ nil,nil,1  ,nil,nil },
	{ nil,nil,nil,nil,nil }
}
T[3]={
	{ nil,nil,nil,nil,nil },
	{ nil,nil,1  ,nil,nil },
	{ nil,1  ,1  ,1  ,nil },
	{ nil,nil,nil,nil,nil },
	{ nil,nil,nil,nil,nil }
}
T[4]={
	{ nil,nil,nil,nil,nil },
	{ nil,nil,1  ,nil,nil },
	{ nil,1  ,1  ,nil,nil },
	{ nil,nil,1  ,nil,nil },
	{ nil,nil,nil,nil,nil }
}

--Z
Z[1]={
	{ nil,nil,nil,nil,nil },
	{ nil,nil,nil,nil,nil },
	{ nil,1  ,1  ,nil,nil },
	{ nil,nil,1  ,1  ,nil },
	{ nil,nil,nil,nil,nil }
}
Z[2]={
	{ nil,nil,nil,nil,nil },
	{ nil,nil,nil,1  ,nil },
	{ nil,nil,1  ,1  ,nil },
	{ nil,nil,1  ,nil,nil },
	{ nil,nil,nil,nil,nil }
}
Z[3]={
	{ nil,nil,nil,nil,nil },
	{ nil,nil,nil,nil,nil },
	{ nil,1  ,1  ,nil,nil },
	{ nil,nil,1  ,1  ,nil },
	{ nil,nil,nil,nil,nil }
}
Z[4]={
	{ nil,nil,nil,nil,nil },
	{ nil,nil,nil,1  ,nil },
	{ nil,nil,1  ,1  ,nil },
	{ nil,nil,1  ,nil,nil },
	{ nil,nil,nil,nil,nil }
}

local SHAPES={ }
SHAPES[1],SHAPES[2],SHAPES[3],SHAPES[4],SHAPES[5],SHAPES[6],SHAPES[7]=I,J,L,O,T,S,Z
return SHAPES
