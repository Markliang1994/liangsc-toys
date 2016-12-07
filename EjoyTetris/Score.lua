local ej = require "ejoy2d"
local fw = require "ejoy2d.framework"
local pack = require "ejoy2d.simplepackage"
local sprite = require "ejoy2d.sprite"
local helper = require "script.helper_ui"
local shader = require "ejoy2d.shader.c"
--score
local SCORE={ }

function SCORE:new(o)
	o = o or { }
	o.score=0
	o.scoreNum=sprite.label { width=60, height=20,size=20,text="0"}
	o.scoreNum:ps(395,13)
	setmetatable(o,self)
	self.__index=self
	return o
end

function SCORE:getScore()
	return self.score
end

function SCORE:setScore(score)
	self.score=self.score+score
	local temp=tostring(self.score)
	self.scoreNum=sprite.label { width=60, height=20,size=20,text=temp }
	self.scoreNum:ps(395,13)
end

function SCORE:drawScore()
	self.scoreNum:draw()
end

function SCORE:reset()
	self.scoreNum.text="0"
end
return SCORE
