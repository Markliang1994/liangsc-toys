local TP=require "script.Piece"
local TD=require "script.TetrisDraw"
local TL=require "script.TetrisLogic"
local GS=require "script.Score"

math.randomseed(os.time())

local TTD=TD:new(o)
local TetrisGame={ }
local SCOREMAP={10,30,50,70}
local indexA,indexB,subIndexA=1,math.random(7),1
local curB,nextB

function TetrisGame:new(o)   --construct and init
	o=o or { }
	o.beginRow,o.beginCol=1,6
	o.currentRow,o.currentCol=o.beginRow,o.beginCol
	o.SCORE=GS:new(s)
	o.STEP=18
	o.beginX,o.beginY=378,78
	o.time1,o.time2=os.clock(),os.clock()
	setmetatable(o,self)
	self.__index=self
	return o	
end

function TetrisGame:getBlo()
	indexA=indexB
	curB=TP:createPiece(indexA,1,378,78)
	repeat 
		indexB=math.random(7)
	until indexB ~= indexA
	nextB=TP:createPiece(indexB,1,637,220)
	return curB
end

function TetrisGame:reset()
	self.currentRow,self.currentCol=self.beginRow,self.beginCol
	self.currentX,self.currentY=self.beginX,self.beginY
end

TetrisGame:getBlo()

function TetrisGame:step(ifover)
	local time3,time4=os.clock(),os.clock()
	if  time3-self.time1 > 0.5 then
		self.time1=time3
		if TTD:ifCanDraw(curB,self.currentRow+1,self.currentCol) then
			self.currentRow=self.currentRow+1
			curB.y=curB.y+18
		else
			TTD:copyState(curB,self.currentRow,self.currentCol,indexA)
			if self.currentRow==1 then
				ifover=true
				return ifover
			end
			self:reset()
			self:getBlo()
		end
	end
	if not TTD:ifCanDraw(curB,self.currentRow,self.currentCol,indexA) and self.currentRow==1 then
		ifover=true
		return ifover
	end
	nextB:draw(indexB)
	curB:draw(indexA)
	self:testFullLine()
	self.SCORE:drawScore()
	TTD:bigDraw()
	return false
end

function TetrisGame:newGame()
	self:reset()
	TTD:reset()
	self:getBlo()
	self.SCORE:reset(0)
end

function TetrisGame:Pause()
	curB:draw(indexA)
	nextB:draw(indexB)
	self.SCORE:drawScore()
	TTD:bigDraw()
end

function TetrisGame:GameOver() 
	nextB:draw(indexB)
	TTD:bigDraw()
	self.SCORE:drawScore()
end

function TetrisGame:testFullLine()
	local level=TTD:removeLine()
	if level~=0 then
		self.SCORE:setScore(SCOREMAP[level])
	end
end

function TetrisGame:rotate()
	local newPiece
	newPiece,subIndexA=curB:rotate(indexA,subIndexA)
	if TTD:ifCanDraw(newPiece,self.currentRow,self.currentCol) then
		newPiece:draw(indexA)
		curB=newPiece
	end
end

function TetrisGame:leftShift()
	if TTD:ifCanDraw(curB,self.currentRow,self.currentCol-1) then
		self.currentCol=self.currentCol-1
		curB:moveLeft(indexA)
	end
end

function TetrisGame:rightShift()
	if TTD:ifCanDraw(curB,self.currentRow,self.currentCol+1) then
		self.currentCol=self.currentCol+1
		curB:moveRight(indexA)
	end
end

function TetrisGame:downShift()
	if TTD:ifCanDraw(curB,self.currentRow+1,self.currentCol) then
		self.currentRow=self.currentRow+1;
		curB:moveDown(indexA)
	end
end

return TetrisGame
